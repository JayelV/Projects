// The module 'vscode' contains the VS Code extensibility API
import * as vscode from 'vscode';
import * as fs from "fs";
import * as path from 'path';
import { spawn } from 'child_process';
import { PythonShell } from 'python-shell';
//DeepL API module
import * as deepl from 'deepl-node';
import { TargetLanguageCode } from 'deepl-node';



const authKey = "1530317e-8614-33a5-7ee6-ff77e9cf2f5b:fx";//API key
const translator = new deepl.Translator(authKey);//create Deepl instance
const dictFilePath = path.join(__dirname, '..', 'dictionaries', 'dict-python.json');
const dictData = JSON.parse(fs.readFileSync(dictFilePath, { encoding: "utf8" })); //parse through our local dictionary 

async function selectLanguage(): Promise<deepl.TargetLanguageCode> {//Used to select Language for APi to translate English to
	const languages = await translator.getTargetLanguages();
	const items = languages.map(lang => ({
	  label: lang.name,//name displayed in dropdown menu
	  code: lang.code, // langauge code
	  picked: lang.code === 'en'
	}));
	const selectedLanguages = await vscode.window.showQuickPick(items, {
	  canPickMany: false,
	  placeHolder: 'Select target language for translation'
	});
	return selectedLanguages?.code as TargetLanguageCode || 'en';
  }
  

export function activate(context: vscode.ExtensionContext) {
	const languageKey = 'selectedLanguage';
	let selectedLanguage = context.globalState.get(languageKey) as deepl.TargetLanguageCode;

	  
	async function getSelectedLanguage(): Promise<deepl.TargetLanguageCode> {
		if (!selectedLanguage) {
		  selectedLanguage = await selectLanguage();
		  context.globalState.update(languageKey, selectedLanguage);
		} else {
		  await selectLanguage();
		}
		return selectedLanguage;
	}

	let updateLanguage = vscode.commands.registerCommand('linguacodex.updateLanguage', async () => {//enables user to select language
		const targetLang = await selectLanguage();
		selectedLanguage = targetLang;
		context.globalState.update(languageKey, selectedLanguage);
	  });
	  
	let apiTranslator = vscode.languages.registerHoverProvider('python', {
		async provideHover(document, position, token) {
		  const range = document.getWordRangeAtPosition(position);
		  const word = document.getText(range);
	  
		  if (word in dictData) {//checks if it is a keyword
			const engDefinition = dictData[word]['en'][1];
			const targetLang = selectedLanguage || await getSelectedLanguage();
			const translated = await translator.translateText(
			  engDefinition,
			  null,
			  targetLang,
			);
			let definition = dictData[word]['en'][0] + ' : ';
			if(targetLang in dictData[word]){//checks if the definition is in the local dictionary already
				definition += '\n'+dictData[`${word}`][`${targetLang}`][0]+"\n"+dictData[`${word}`][`${targetLang}`][1];
			} else {
				if (Array.isArray(translated)) {
				definition += '\n' + translated.map(t => t.text).join('\n');
				} else {
				definition += '\n' + translated.text;
				}
			}
			return new vscode.Hover(`${definition}`);
		  }
		},
	});
	  
	let translateKeyword = vscode.commands.registerCommand('linguacodex.translateKeyword', async () => {
		const editor = vscode.window.activeTextEditor;
		if(editor){	
		const selection = editor.selection;
		const text = editor.document.getText(selection);
		let newText = text;
		for (const wordToReplace in dictData) {
			const engDefinition = dictData[wordToReplace]['en'][0];
			const targetLang = selectedLanguage || await getSelectedLanguage();
			const translated = await translator.translateText(
			  engDefinition,
			  null,
			  targetLang,
			);
			let definition = '';//definition to replace keyword with 
			if(targetLang in dictData[wordToReplace]){//checks if the definition is in the local dictionary already
				definition += dictData[`${wordToReplace}`][`${targetLang}`][0];
			} else {
				if (Array.isArray(translated)) {
				definition += translated.map(t => t.text).join('\n');
				} else {
				definition += translated.text;
				}
			}
			newText = newText.replace(new RegExp(`\\b${wordToReplace}\\b`, 'gi'), definition);
		  	//newText = newText.replace(new RegExp(`\\b${wordToReplace}\\b`, 'gi'), dictData[`${wordToReplace}`]["Spanish"][0]);
		}
		editor.edit(editBuilder => {
		  editBuilder.replace(selection, newText);//
		});
	  }
	});

	console.log('Congratulations, your extension "linguacodex" is now active hi!');// check to see if extension is running

	// push all commands and hover providers
	context.subscriptions.push(apiTranslator);
	context.subscriptions.push(updateLanguage);
	context.subscriptions.push(translateKeyword);
  }

// This method is called when your extension is deactivated
export function deactivate() {}
