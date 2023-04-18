import React, { Component } from 'react';
import { Image, Text, View, ScrollView, Button, Alert, TouchableOpacity } from 'react-native';

import styles from './styles'

export default class NewItems extends Component {
    /*A section that includes the 3 newest items at cage
         that have been entered in the database - updates 
         as newer items entered */ 
    constructor (props) {
        super(props);
    }

    render() {
        return (
            <View style={styles.section}>
                <Text style={styles.text}> 
                    NEW ITEMS!
                </Text>
                <Text>    Nothing here for now!</Text>
                <Text>    Check back later :D</Text>
            </View>
        )
    }
}



