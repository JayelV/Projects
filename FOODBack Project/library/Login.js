import React, { Component } from 'react';
import { Image, StyleSheet, Text, Button, View, TextInput } from 'react-native';

export default class Login extends Component {
    constructor(props) {
        super(props);
        this.state = {
            app_icon: 'https://i.imgur.com/qlrJbhC.png',
            url: 'http://10.42.238.66:3001',
            formContentType: "application/x-www-form-urlencoded;charset=UTF-8", 
            username: 'username',
            pin: '0000',
            uid: 0,
        };
    
      }
      handlePress = (op, method = '', params = {}) => {
        if (method != '')
            params.method = method;
        fetch(this.state.url + '/'+op, params)
            .then((response) => response.text())
            .then((responseText) => {
                console.log("res: "  + `${responseText}`);
                if (`${responseText}` == '') {
                     console.log("Incorrect password.");
                    // display wrong input 
                    alert("Wrong information inputed; try again.");  
                    return; 
                }
                // set user id and change to home
                let uid_login = `${responseText.split(":")[1].split('}')[0]}`;
                this.setState({uid: uid_login})
                console.log("Correct password... logging in...");
                console.log("uid: " + this.state.uid);
                global.uid = this.state.uid;
                return this.props.navigation.navigate('Home'); 
            })
            .catch((error) => {
                console.error(error);
            });
      }

    render() {
        return(
            <View style={styles.container}>
                <Image source={{uri: this.state.app_icon}} style={{margin: 10, width: '40%', aspectRatio: 1,}} />
                {/* <Text style={{padding: 10,}}>Welcome to FOODBack</Text> */}
                <TextInput 
                    style={styles.input} 
                    placeholder={'Enter username'}
                    onChangeText={(username)=> this.setState({username})} />
                <TextInput 
                    style={styles.input} 
                    placeholder={'Enter pin'} 
                    onChangeText={(pin) => this.setState({pin}) }/>
                    <Button
                        title='LOGIN'
                        color='#664004'
                        onPress={() => this.handlePress('login', 'PUT', {
                            headers: {
                            "Content-type": this.state.formContentType
                            }, 
                        body: `login_info=${this.state.username},${this.state.pin}`

                        }
                    )}/>
                    <Button title= 'Register' 
                    onPress={() => this.props.navigation.navigate('Register') }/>
                 

            </View>
        );
    }
}

const styles = StyleSheet.create({
    container: {
        paddingTop: 100,
        flex: 1,
        backgroundColor:'white',
        alignItems: 'center',
        // justifyContent: 'center'
        // backgroundColor: '',
    },
    input:{
        // padding: 10,
        margin: 5,
        paddingVertical:15,
        paddingHorizontal: 15,
        backgroundColor: '#d6993a',
        borderColor: 'black',
        borderWidth: 1,
  
        width: '60%',
    },
});