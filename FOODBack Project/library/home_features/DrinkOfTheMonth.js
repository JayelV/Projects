import React, { Component } from 'react';
import { Image, Text, View, ScrollView, Button, Alert, TouchableOpacity } from 'react-native';

import styles from './styles'

export default class DrinkOfTheMonth extends Component {
    constructor (props) {
        super(props);
    }

    render() {
        return (
            <View style={styles.section}>
                <Text style={styles.text}> 
                DRINK OF THE MONTH
                </Text>
                <Text>    Maple Latte {'\t\t\t\t\t\t\t'}★★★★☆ </Text>
                <Text>    Prickly Pear IS {'\t\t\t\t\t\t\t'}★★★☆☆ </Text>


            </View>
        )
    }

}




