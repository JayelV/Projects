import React, { Component, useState, useEffect } from 'react';
import { View, Image, Text, StyleSheet, Button } from 'react-native';


function Photo (props) {
    /*A section that includes the 3 newest items at cage
         that have been entered in the database - updates 
         as newer items entered */ 

    const url = 'http://10.42.238.66:3001';
    const formContentType = "application/x-www-form-urlencoded;charset=UTF-8";

    const handlePress = (op, method = '', params = {}) => {
        if (method != '')
            params.method = method;
	console.log(`received request ${op}, ${method}`)
        fetch(url + '/'+op, params)
            .then((response) => response.text())
            .then((responseText) => {
		console.log(`response text: ${responseText}`)
                alert(`
                    Sent:  op=${JSON.stringify(op)}\nparams+method=${
			JSON.stringify(params)}\n
                    Received:  ${responseText}`);
            })
            .catch((error) => {
                console.error(error);
            });
    }

    const [trash, setTrash] = useState('');

    const onLoad = ( ) => {
        // console.log('uid:' + uid);
        // console.log('photo_uid: ' + props.photo_uid);

        if(props.photo_uid == uid) {
            // update trash 
            setTrash('X');        
        } else { setTrash('') }
    }

    useEffect(() => {
        onLoad();
    }, []);


    // const handleDeleteComment 
    const handleDeletePhoto= (op, method = '', params = {}) => {
        if (method != '')
            params.method = method;
	console.log(`received request ${op}, ${method}`)
        fetch(url + '/'+op, params)
            .then((response) => response.text())
            .then((responseText) => {
		console.log(`response text: ${responseText}`)
            //     alert(`
            //         Sent:  op=${JSON.stringify(op)}\nparams+method=${
			// JSON.stringify(params)}\n
            //         Received:  ${responseText}`);
            alert("Photo deleted. Refresh the page.");
            })
            .catch((error) => {
                console.error(error);
            });
    }

    const deletePhoto = ( ) => {
        if (props.photo_uid == uid) {
            setTrash('');
            // DELETE item: 
            handleDeletePhoto('photos', 'DELETE', {
                    headers: {
                        "Content-type": formContentType
                    }, 
                        body: `pid=${props.pid}`
                    }
            
            );
        }
    }

    return (
        <View>
            <View style={styles.date}>
                    <Text style={{paddingBottom: 10, fontSize:12,}}>Posted on: {props.date} </Text>    
                    <View style={{marginTop: -20}}>
                    <Button 
                        color='red'
                        title={trash}
                        onPress={() => deletePhoto()}
                        />
                </View>     
            </View>

                
            <Image source={{uri: props.uri}} style={{margin: 10, width: '95%', aspectRatio: 1.8,}} />
            <View
                style={{
                borderBottomColor: 'grey',
                borderBottomWidth: 1,
                }}/>
        </View>
    );
}

const styles = StyleSheet.create({
    date:{
        display: 'flex',
        flex: 1,
        paddingTop: 10,
        marginBottom: -10,
        // marginLeft: 'auto',
        justifyContent: 'space-between',
        // direction: 'rtl',
        alignItems: 'flex-end',

        flexDirection: 'row'
        // paddingBottom: 5,

    },
});


export default Photo;