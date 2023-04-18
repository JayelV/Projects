import React,  { useState, Component, useEffect } from 'react';
import { Image, Text, View, TextInput, ScrollView, Button, Alert, TouchableOpacity, KeyboardAvoidingView, Platform, Keyboard } from 'react-native';

import styles from './home_features/styles'
import Photo from './photo_gallery/Photo'


function FoodGallery(props) {

    const [photoURL, setPhotoURL] = useState(); // 
    // const [photoItems, setPhotoItems] = useState([["https://i.imgur.com/waOOzyl.jpg", 1], ['https://i.imgur.com/rcUWRq1.jpg', 2]]); // 
    const [photoItems, setPhotoItems] = useState([]); // 

    // setPhotoItems([]);

    const app_logo = 'https://i.imgur.com/dt5dJEI.png';
    
    const url = 'http://10.42.238.66:3001';
    const formContentType = "application/x-www-form-urlencoded;charset=UTF-8";
    

    const handleAddPhoto = (op, method = '', params = {}) => {
        if (method != '')
            params.method = method;
        fetch(url + '/'+op, params)
            .then((response) => response.text())
            .then((responseText) => {
                Keyboard.dismiss();
                let arr = [];
                arr.push(`${responseText.url}`);
                arr.push(`${responseText.uid}`);
                arr.push(0);
                arr.push('2021-11-11');

                setPhotoItems([...photoItems, arr]);
                // setPhotoURL(null);

            })
            .catch((error) => {
                console.error(error);
            });
      }

      const handlePressPhotos = (op, method = '', params = {}) => {
        if (method != '')
            params.method = method;
        fetch(url + '/'+op, params)
            .then((response) => response.json()) // response.json()
            .then((responseText) => {
                let len = responseText.length;
                let twod_arr = [];
                for (let i = 0; i < len; i++) {
                    let arr = [];
                    // console.log("ITERATION " + i);
                    arr.push(`${responseText[i].url}`);     // index = 0 : url
                    // console.log(`${responseText[i].url}`);
                    arr.push(`${responseText[i].uid}`);     // index = 1 : uid
                    // console.log(`${responseText[i].uid}`);

                    arr.push(`${responseText[i].pid}`);     // index = 2 : pid
                    // console.log(`${responseText[i].pid}`);  
                    let date = `${responseText[i].date}`;   // index = 3 : date
                    date = date.substr(0, 10);
                    arr.push(date);
                    // console.log('date: ' + date);
                    twod_arr.push(arr);
                }

                setPhotoItems([]); // empties comments so far to refresh 
                setPhotoItems(twod_arr);
                console.log(photoItems);
            })
            .catch((error) => {
                console.error(error);
            });
    }

    
    useEffect(() => {
        handlePressPhotos('photos','GET');
    }, []);


    return (
        <View style={styles.container}>
        <View style={styles.header1}></View>

        <View style={styles.header2}>
            <Image source = {{uri: app_logo}} style={{margin: 10, height: '100%', aspectRatio: 1.8,}} />
        </View>
  
        <View style={styles.body}>
            <ScrollView style={styles.scrollView}>

                <View style={styles.section}> 
                    <View style={styles.cafHeader}>
                        <Text style={styles.text}>FOOD GALLERY</Text>
                        <Button color="black"  title="⟳" 
                            onPress={()=> handlePressPhotos('photos','GET')}/> 
                    </View>
                    <View
                        style={{
                        borderBottomColor: 'grey',
                        borderBottomWidth: 1,
                        }}/>                     
                    {
                        photoItems.map((item, index) => {
                            return <Photo key={index} uri={`${item[0]}`} photo_uid={`${item[1]}`} pid={`${item[2]}`}  date={`${item[3]}`}  />
                        })
                    }

                </View> 
                


            </ScrollView>
            <KeyboardAvoidingView 
                    keyboardVerticalOffset = {150} 
                    behavior={Platform.OS === "ios" ? "padding" : "height"}
                    style={styles.writeCommentWrapper}>
            
                    <TextInput style={{padding: 15, backgroundColor: '#e6e6e6', borderColor: '#c0c0c0', borderWidth: 1, fontWeight: 'bold', width: '87%' }} 
                        placeholder={'Paste a url'} value={photoURL} onChangeText={text => setPhotoURL(text)} />
                    <TouchableOpacity onPress={()=>handleAddPhoto('photos', 'POST', {
                        headers:{
                            "Content-type": formContentType
                        },
                        body: `url=${photoURL}&uid=${uid}`
                    })}>
                    <View style={styles.addWrapper}>
                        <Text style={styles.addText}>+</Text>
                    </View>
                    </TouchableOpacity>
                </KeyboardAvoidingView>
        </View>


        {/* NAVIGATION CODE BELOW */}
        <View style={styles.nav}>
          <Button title="🏠"
            onPress={() => props.navigation.navigate('Home')}/>
          {/* <Button title="💬"
            onPress={() => this.handlePressComments('comments','GET')}/> */}
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

export default FoodGallery;