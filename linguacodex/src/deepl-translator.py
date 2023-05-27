import deepl

translator = deepl.Translator("1530317e-8614-33a5-7ee6-ff77e9cf2f5b:fx")
def translatex(en_definition, target):
    result = translator.translate_text(text=en_definition, source_lang="EN", target_lang=target)
    return result