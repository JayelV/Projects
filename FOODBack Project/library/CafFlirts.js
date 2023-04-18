import React, { Component } from 'react';
import { Image, ScrollView, StyleSheet, Text, Button, View, TextInput } from 'react-native';

import styles from './home_features/styles'
// import Home from './Home'
// import CafComments from './CafComments';




export default class Login extends Component {
    constructor(props) {
        super(props);
        this.state = {
            app_logo: 'https://i.imgur.com/dt5dJEI.png',
            
        }
      }

    render() {
        return( 
        
        <View style={styles.container}>
            <View style={styles.header1}></View>

            <View style={styles.header2}>
                <Image source = {{uri: this.state.app_logo}} style={{margin: 10, height: '100%', aspectRatio: 1.8,}} />
            </View>
      
            <View style={styles.body}>
                <ScrollView style={styles.scrollView}>
                    <View style={{alignItems: 'center', justifyContent: 'center', paddingTop: 250}}>
                        <Text style={{padding: 5, fontWeight: 'bold', fontSize: 16}}>🖤🖤🖤🖤🖤🖤🖤 🖤🖤🖤🖤🖤🖤</Text> 
                        <Text style={{padding: 5, fontWeight: 'bold', fontSize: 16}}>🖤 CAF FLIRTS PAGE COMING SOON 🖤</Text>
                        <Text style={{padding: 5, fontWeight: 'bold', fontSize: 16}}>🖤🖤🖤🖤🖤🖤🖤 🖤🖤🖤🖤🖤🖤</Text> 
                    </View>
                </ScrollView>
                {/* <NavBar/> */}
            </View>

            <View style={styles.nav}>
              <Button title="🏠"
                onPress={() => this.props.navigation.navigate('Home')}/>
              {/* <Button title="💬"
                onPress={() => this.handlePressComments('comments','GET')}/> */}
                <Button title="💬"
                onPress={() => this.props.navigation.navigate({name: 'CafComments', params:{text_hello: 'Caf Comments'}})}/>
             <Button title="🖼️"
                onPress={() => this.props.navigation.navigate('FoodGallery')}/>
              <Button title="🖤"
                onPress={() => this.props.navigation.navigate('CafFlirts')}/>
            </View>
            
        </View>
            
            );
    }
}
