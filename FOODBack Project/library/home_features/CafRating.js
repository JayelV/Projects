import React, { Component, useState, useEffect} from 'react';
import { Image, Text, View, ScrollView, Button, Alert, TouchableOpacity } from 'react-native';

import styles from './styles'






function CafRating(props) {

    const [greenBar, setGreenBar] = useState(props.p_green);
    const [redBar, setRedBar] = useState(props.p_red);
    
    return (
        <View style={styles.section}>
            <View style ={{flexDirection: 'row', justifyContent: 'space-between'}}>
                <Text style={styles.text}> TODAY'S CAF RATING </Text>
            </View>
            
            
            <View style={{flexDirection: 'row', justifyContent: 'space-between', marginTop: 0,}}>
                <Text> {'\t'}Based on Caf feedback: </Text>
                <Text style={styles.progbar}>{props.p_green}<Text style={styles.progbar2}>{props.p_red}</Text>	 </Text>

            </View>
        </View>

        
    );


}

export default CafRating;