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
        };
    
      }

      handlePress = (op, method = '', params = {}) => {
        if (method != '')
            params.method = method;
	console.log(`received request ${op}, ${method}`)
        fetch(this.state.url + '/'+op, params)
            .then((response) => response.text())
            .then((responseText) => {
		console.log(`response text: ${responseText}`)
                alert(`You've successfully registered.`);
                return this.props.navigation.navigate('Login'); 
            })
            .catch((error) => {
                console.error(error);
            });
        }

    render() {
        return(
            <View style={styles.container}>
                {/* <Image source={{uri: this.state.app_icon}} style={{margin: 10, width: '40%', aspectRatio: 1,}} /> */}
                <Text style={{padding: 10, fontWeight: 'bold'}}>Enter a username and a 4 digit pin.</Text>
                <TextInput 
                    style={styles.input} 
                    placeholder={'Enter username'}
                    onChangeText={(username)=> this.setState({username})} />
                <TextInput 
                    style={styles.input} 
                    placeholder={'Enter pin'} 
                    onChangeText={(pin) => this.setState({pin}) }/>
                {/* <TextInput 
                    style={styles.input} 
                    placeholder={'Enter pin again'} 
                    onChangeText={(pin) => this.setState({pin}) }/> */}
                    <Button
                        title='REGISTER'
                        color='#664004'
                        onPress={() => this.handlePress('register', 'POST', {
                            headers: {
                            "Content-type": this.state.formContentType
                            }, 
                        body: `username=${this.state.username}&pin=${this.state.pin}`

                        }
                    )}/>
                    {/* <Button title= 'Register'/> */}
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