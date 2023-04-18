import React, { Component } from 'react';
import { Image, Text, View, ScrollView, Button, Alert, TouchableOpacity } from 'react-native';

import styles from './styles'

export default class HotAtCage extends Component {
    constructor (props) {
        super(props);
    }

    render() {
        return (
            <View style={styles.section}>
                <Text style={styles.text}> HOT 🔥 @ CAGE </Text>
                
                <Text style={{fontWeight: 'bold',}}>     DRINKS </Text>
                <Text >{'\t'}🔥 Mango Lemonade </Text>
                <Text >{'\t'}🔥 Iced Latte </Text>
                <Text >{'\t'}🔥 Stawberry Italian Soda </Text>

                <Text style={{fontWeight: 'bold',}}>     FOOD </Text>
                <Text >{'\t'}🔥 Garlic Aioli Burger </Text>
                <Text >{'\t'}🔥 St. Olaf Burger </Text>
                <Text >{'\t'}🔥 Impossible Burger </Text>
            </View>
            
        )
    }

}




