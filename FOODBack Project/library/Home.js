import React, { Component, useEffect, useState } from 'react';
import { Image, Text, View, ScrollView, Button, Alert, TouchableOpacity } from 'react-native';

import styles from './home_features/styles'
import CafRating from './home_features/CafRating';
import HotAtCage from './home_features/HotAtCage';
import DrinkOfTheMonth from './home_features/DrinkOfTheMonth';
import NewItems from './home_features/NewItems';
import CafFlirts from './CafFlirts'
import FoodGallery from './FoodGallery';


function Home (props) {

    let app_logo = 'https://i.imgur.com/dt5dJEI.png';
    let app_icon = 'https://i.imgur.com/qlrJbhC.png';
    let url =  'http://10.42.238.66:3001';
    let loaded_comments = ['HELLO'];
    let hot_at_cage_food = '**** here is hot cage foods'; // MAKE THIS STATE VAR
    // let uid = 0;


    const handlePressGetHot = (op, method = '', params = {}) => {
      if (method != '')
          params.method = method;
      fetch(url + '/'+op, params)
          .then((response) => response.json())
          .then((responseText) => {
            // this.setState({hot_at_cage_food: `${responseText[0].item}`}); // hot_at_cage_food = responseText
            hot_at_cage_food = `${responseText[0].item}`;
            console.log(hot_at_cage_food);
          })
          .catch((error) => {
              console.error(error);
          });
    }



    const [pGreen, setPGreen] = useState('██████');
    const [pRed, setPRed] = useState('██████');

    const handleGetCafRating = (op, method = '', params = {}) => {
      if (method != '')
          params.method = method;
      fetch(url + '/'+op, params)
          .then((response) => response.json())
          .then((responseText) => {
            console.log("uid: " + props.uid);

            if (`${responseText.name_val[0]}` == 'undefined') {return;}
            if (`${responseText.name_val[1]}` == 'undefined') {
              // console.log(`${responseText.name_val[0]}`);
              if (`${responseText.name_val[0].split("|")[0]}` == 'green') {
                setPGreen('████████████')
                setPRed('');
              } else { setPRed('████████████')
              setPGreen(''); }
              return;}  

            setPGreen('');
            setPRed('');
            let nGreen = parseInt(`${responseText.name_val[0].split("|")[1]}`);
            let nRed = parseInt(`${responseText.name_val[1].split("|")[1]}`);

            let n = nGreen+nRed;
            let green = Math.round((12*nGreen)/(n));
            let  red = Math.round((12*nRed)/(n));

            let green_draw = '';
            for (let i = 0; i < green; i++) {
              green_draw += '█';
            }
            setPGreen(green_draw);
            
            let red_draw = '';
            for (let i = 0; i < red; i++) {
              red_draw += '█';
            }
            setPRed(red_draw);

          })
          .catch((error) => {
              console.error(error);
          });
    }

  useEffect(() => {
      handleGetCafRating('green/red','GET');
  }, []);

      return (
        <View style={styles.container}>
            <View style={styles.header1}></View>

            <View style={styles.header2}>
                <Image source = {{uri: app_logo}} style={{margin: 10, height: '100%', aspectRatio: 1.8,}} />
            </View>
      
            <View style={styles.body}>
                <ScrollView style={styles.scrollView}>

                  {/* <Text>user id: {uid}</Text> */}
                    {/* <CafRating p_green = {pGreen} p_red ={pRed}/> */}
                <View style={styles.section}>
                    <View style ={{flexDirection: 'row', justifyContent: 'space-between'}}>
                        <Text style={styles.text}> TODAY'S CAF RATING </Text>
                    </View>
                    
                    
                    <View style={{flexDirection: 'row', justifyContent: 'space-between', marginTop: 0,}}>
                        <Text> {'\t'}Based on Caf feedback: </Text>
                        <Text style={styles.progbar}>{pGreen}<Text style={styles.progbar2}>{pRed}</Text>	 </Text>

                    </View>
                </View>

                    <HotAtCage/>
                    {/* <Text>
                      {hot_at_cage_food}
                    </Text> */}
                    {/* <Button
                        color='green' title='Click to see the first 3 foods'
                        onPress={() => handlePressGetHot('hot_at_cage', 'GET')} /> */}
                    <DrinkOfTheMonth/>       
                    <NewItems/>             
                </ScrollView>
                {/* <NavBar/> */}
            </View>

            <View style={styles.nav}>
              <Button title="🏠"
                onPress={() => props.navigation.navigate('Home')}/>
                <Button title="💬"
                onPress={() => props.navigation.navigate({name: 'CafComments', params:{text_hello: 'Caf Comments'}})}/>
                <Button title="🖼️"
                onPress={() => props.navigation.navigate('FoodGallery')}/>
              <Button title="🖤"
                onPress={() => props.navigation.navigate('CafFlirts')}/>
            </View>
            
        </View>
        

      );
  }

  export default Home;