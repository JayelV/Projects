import React, { Component } from 'react';
import { Button, View, Text, TextInput} from 'react-native';

import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';

import CafComments from './library/CafComments';
import Home from './library/Home';
import Login from './library/Login';
import LikeButton from './LikeButton';
import CafFlirts from './library/CafFlirts'
import Register from './library/Register'
import FoodGallery from './library/FoodGallery';

const Stack = createStackNavigator();

export default class MyApp extends Component {
  constructor(props) {
    super(props);
    this.state = {
      url: 'http://10.42.238.66:3001',
    };
  }

  handlePress = (op, method = '', params = {}) => {
    if (method != '')
        params.method = method;
    fetch(this.state.url + '/'+op, params)
        .then((response) => response.text())
        .then((responseText) => {
            alert(`
                Sent:  op=${JSON.stringify(op)}\nparams+method=${
  JSON.stringify(params)}\n
                Received:  ${responseText}`);
        })
        .catch((error) => {
            console.error(error);
        });
  }


  render() {
    return (
      <NavigationContainer>
        <Stack.Navigator>
          <Stack.Screen name="Login" component={Login} />
          <Stack.Screen name="Register" component={Register} />
          <Stack.Screen name="Home" component={Home} />
          <Stack.Screen name="CafComments" component={CafComments}/>
          <Stack.Screen name="FoodGallery" component={FoodGallery}/>
          <Stack.Screen name="CafFlirts" component={CafFlirts}/>
        </Stack.Navigator>      
      </NavigationContainer>
    );
  }
}

