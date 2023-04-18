import React,  { useState, Component, useEffect } from 'react';
import { Image, Text, View, TextInput, ScrollView, Button, Alert, TouchableOpacity, KeyboardAvoidingView, Platform, Keyboard } from 'react-native';
import BouncyCheckbox from "react-native-bouncy-checkbox";

import styles from './home_features/styles'
import Comment from './comment_feature/Comment'
import CafFlirts from './CafFlirts'
import Carousel2 from './comment_feature/Carousel_Components';

const images = [
    'https://i.imgur.com/PPw39U3.jpg',
    'https://i.imgur.com/2kHbLFO.jpg',
    'https://i.imgur.com/5hQxVZg.jpg',
    'https://i.imgur.com/qQ97QEx.jpg',
    'https://i.imgur.com/rcUWRq1.jpg'
]

function CafComments(props) {
    
    // var state_comments = 0;
    const [stateComments, setStateComments] = useState(0);
    const [commentVote, setCommentVote] = useState('null'); // 
    
    // setStateComments(0);
    let url = 'http://10.42.238.66:3001';
    let formContentType="application/x-www-form-urlencoded;charset=UTF-8";

    const [comment, setComment] = useState(); // setComment("com");
    const [commentItems, setCommentItems] = useState([]); // 
    const [commentItemsDetails, setCommentItemsDetails] = useState([]);
    // POS/NEG checkbox
    const [checkboxState, setCheckboxState] = React.useState(false);
    const [commentVibe, setCommentVibe] = useState("POS");
    const [checkboxColor, setCheckboxColor] = useState("green");

    const changeCommentVibe = () => {
        setCheckboxState(!checkboxState);
        if (checkboxState == true){
            //meaning that it's positive:
            setCommentVibe("POS");
            setCheckboxColor("green");
        } else { // negative 
            setCommentVibe("NEG");
            setCheckboxColor("red");
        }

    }

    handleAddComment = (op, method = '', params = {}) => {
        if (method != '')
            params.method = method;
        fetch(url + '/'+op, params)
            .then((response) => response.text())
            .then((responseText) => {
                Keyboard.dismiss();
                let arr = [];
                arr.push(comment);
                if (checkboxState == true) { arr.push('red'); } else { arr.push('green')}
                arr.push(0);
                arr.push(`2021-11-11`);
                setCommentItems([...commentItems, arr]);
                setComment(null);

            })
            .catch((error) => {
                console.error(error);
            });
      }

    const handleFindVoteStatus = (op, method = '', params = {}) => {
        if (method != '')
            params.method = method;
        fetch(url + '/'+op, params)
            .then((response) => response.json()) // response.json()
            .then((responseText) => {
              console.log(responseText);

              // DO STUFF HERE --> for every comment look for if user with uid responded. 

            })
            .catch((error) => {
                console.error(error);
            });
    }

    
    const handlePressComments = (op, method = '', params = {}) => {
        if (method != '')
            params.method = method;
        fetch(url + '/'+op, params)
            .then((response) => response.json()) // response.json()
            .then((responseText) => {
            //   let l_comments = responseText.split('\"');  
              console.log(responseText);

              let len = responseText.length;
              console.log("len: " + len);

              let twod_arr = [];
              for (let i = 0; i < len; i++) {
                let arr = [];
                // console.log("ITERATION " + i);
                arr.push(`${responseText[i].comment}`);
                arr.push(`${responseText[i].neg_feedback}`);
                arr.push(`${responseText[i].votes}`);
                let date = `${responseText[i].date}`; 
                date = date.substr(0, 10);
                arr.push(date);
                arr.push(`${responseText[i].uid}`)
                arr.push(`${responseText[i].cid}`)
                twod_arr.push(arr);
                arr.push('null');
            }   

                setCommentItems([]); // empties comments so far to refresh 
                setCommentItems(twod_arr);
            })
            .catch((error) => {
                console.error(error);
            });
    }

    
    let app_logo = {
        uri: 'https://i.imgur.com/dt5dJEI.png'
    };

    useEffect(() => {
        handlePressComments('comments','GET');
    }, []);

      return (
        <View style={styles.container}>
            <View style={styles.header1}></View>
            <View style={styles.header2}>
                <Image source={app_logo} style={{margin: 10, height: '100%', aspectRatio: 1.8,}} />
            </View>
      
            <View style={styles.body}>


                <ScrollView style={styles.scrollView}>
                    <Carousel2 images={images}/>

                    <View style={styles.section}>
                        <View style={styles.cafHeader}>
                            <Text style={styles.text}>Caf Comments</Text>
                            {/* <Text>user id: {uid}</Text> */}
                            
                            <Button color="black"  title="⟳" 
                                onPress={() => handlePressComments('comments','GET')}/>
                        </View>
                        {/* <Image source={{uri: 'https://i.imgur.com/waOOzyl.jpg'}} style={{margin: 10, width: '90%', aspectRatio: 1.8,}} /> */}
                        {/* <AppCarousel/> */}
                        <View
                            style={{
                            borderBottomColor: 'grey',
                            borderBottomWidth: 1,
                            }}/>
                        <View style={styles.comments}>
                            {/* This is where one comment will be */}
                            
                            {
                                // console.log(commentItems);
                                commentItems.map((item, index) => {    
                                     return <Comment key={index} 
                                            text={`${item[0]}`} color={`${item[1]}`} 
                                            votes={`${item[2]}`} date={`${item[3]}`} 
                                            post_uid={`${item[4]}`} cid={`${item[5]}`} 
                                            comment_vote={commentVote} />
                                     })
                            }

                            
                        </View>
                    </View>
                    
                </ScrollView>

                <KeyboardAvoidingView 
                    keyboardVerticalOffset = {150} 
                    behavior={Platform.OS === "ios" ? "padding" : "height"}
                    style={styles.writeCommentWrapper}>
                    <View style={{borderWidth: 1, marginBottom: -4, height: '108%', borderColor: '#c0c0c0', paddingTop: 2.3,}}>
                        <Text style={{color: checkboxColor, fontWeight: 'bold', marginBottom: 0, paddingLeft:2.7, marginHorizontal: 10,}}>{commentVibe}</Text>
                    <BouncyCheckbox
                                style={{ paddingBottom:2, marginHorizontal: 15,}}
                                fillColor='red'
                                isChecked={checkboxState}
                                // onPress={() => setCheckboxState(!checkboxState)}
                                onPress={() => changeCommentVibe()}
                        />
                    </View>

                    <TextInput style={{padding: 15, backgroundColor: '#e6e6e6', borderColor: '#c0c0c0', borderWidth: 1, color: `${checkboxColor}`, fontWeight: 'bold', width: '87%' }} 
                        placeholder={'Write a comment'} value={comment} onChangeText={text => setComment(text)} />
                    <TouchableOpacity onPress={() => handleAddComment('comments','POST', {
                        headers:{
                            "Content-type": formContentType
                        },
                        body: `comment=${comment}&feedback=${checkboxState}&uid=${uid}`
                    })}>
                    
                    
                    <View style={styles.addWrapper}>
                        <Text style={styles.addText}>+</Text>
                    </View>
                    </TouchableOpacity>
                </KeyboardAvoidingView>
                
            </View>

            <View style={styles.nav}>
                    <Button title="🏠"
                        onPress={() => props.navigation.navigate("Home")}/>   
                    <Button title="💬"/> 
                    <Button title="🖼️"
                        onPress={() => props.navigation.navigate('FoodGallery')}/>  
                    <Button title="🖤"
                         onPress={() => props.navigation.navigate('CafFlirts')}/>
            </View>
            
        </View>
        

      );

  } // props.route.

  export default CafComments;

