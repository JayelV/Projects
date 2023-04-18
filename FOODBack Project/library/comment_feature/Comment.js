import React, { Component, useState, useEffect } from 'react';
import { View, Text, StyleSheet, Button } from 'react-native';


function Comment (props) {
    /*A section that includes the 3 newest items at cage
         that have been entered in the database - updates 
         as newer items entered */ 

    const url = 'http://10.42.238.66:3001';
    const formContentType = "application/x-www-form-urlencoded;charset=UTF-8";


    const [trash, setTrash] = useState('');

    const unpressed = 'black';
    const pressed = 'red';

    const [comVotes, setComVotes] = useState(parseInt(props.votes,10));

    const [up, setUp] = useState([0, unpressed, 'up']);
    const [down, setDown] = useState([0, unpressed,'dw']);


    const onLoad = ( ) => {
        if(props.post_uid == uid) {
            // update trash 
            setTrash('x');        
        } else { setTrash('') }
    }

    const initVotes = (op, method = '', params = {}) => {
        if (method != '')
            params.method = method;
	// console.log(`received request ${op}, ${method}`)
        fetch(url + '/'+op, params)
            .then((response) => response.text())
            .then((responseText) => {
                if (`${responseText}` == '') {
                    // console.log('NULL RESPONSE...');
                } else {
                    // 'NON NULL RESP';
                    var response = `${responseText.split(':')[1].split('\"')[1]}`;
                    // console.log(response);
                }

                if (response == 'upvote') {
                    // console.log('ENETERED UPVOTE');
                    setUp([1, pressed, 'UP']);
                    setDown([0, unpressed,'dw']);
                } else if (response == 'downvote') {
                    setUp([0, unpressed, 'up']);
                    setDown([1, pressed,'DW']);
                } else { // no votes by user yet
                    }
            })
            .catch((error) => {
                console.error(error);
            });
    }

    useEffect(() => {
        onLoad();
        initVotes('votes', 'PUT', {
            headers: {
                "Content-type": formContentType
            }, body: `cid=${props.cid}&uid=${uid}` });
    }, []);


    const handleDeleteComment = (op, method = '', params = {}) => {
        if (method != '')
            params.method = method;
	console.log(`received request ${op}, ${method}`)
        fetch(url + '/'+op, params)
            .then((response) => response.text())
            .then((responseText) => {
                console.log(`response text: ${responseText}`);
                alert("Comment deleted. Refresh the page.");
            })
            .catch((error) => {
                console.error(error);
            });
    }

    // const handleDeleteComment 

    const deleteComment = ( ) => {
        if (props.post_uid == uid) {
            setTrash('');
            // DELETE item: 
            handleDeleteComment('comments', 'DELETE', {
                    headers: {
                        "Content-type": formContentType
                    }, 
                        body: `cid=${props.cid}`
                    }
            );
        }
    }

    // VOTES VARIABLES AND METHODS :
          
    const upvote = () => { 
        setUp([1, pressed, 'UP']); 
        let update = comVotes + 1; 
        console.log("update: " + update);
        setComVotes(update);
        return update;
    }
    const rmupvote = () => { 
        setUp([0, unpressed, 'up']); 
        let update = comVotes - 1;
        setComVotes(update);
        return update;
    }

    const switchVote = (response) => {
        let update = comVotes + 0;
        if (response == 'upvote') {
            setUp([1, pressed, 'UP']); 
            setDown([0, unpressed, 'dw']); 
            //switch to upvote ++2
            update += 2;
            setComVotes(update);
        } else { // switch to downvote --2
            setDown([1, pressed, 'DW']); 
            setUp([0, unpressed, 'up']); 

            update -= 2;
            setComVotes(update);
        }

        console.log("SWITCH UPDATE: "   + update + "  ||  ||  ||  update type: " + typeof(update));
        
        return update;

    }

    const downvote = () => { 
        setDown([1, pressed, 'DW']); 
        let update = comVotes - 1;
        setComVotes(update);
        console.log("DOWNVOTE UPDATE: "   + update + "  ||  ||  ||  update type: " + typeof(update));
        return update;

    }
    const rmdownvote = () => { 
        setDown([0, unpressed, 'dw']); 
        let update = comVotes + 1;
        setComVotes(update);
        return update;
    } 

    
    /* ---------------------------------------------------------------------------------------- */
    /* VOTE HANDLERS  ------------------------------------------------------------------------- */
    /* ---------------------------------------------------------------------------------------- */

    const handleVotePress = (op, method = '', params = {}) => {
        if (method != '')
            params.method = method;
	console.log(`received request ${op}, ${method}`)
        fetch(url + '/'+op, params)
            .then((response) => response.text())
            .then((responseText) => {
                console.log(`response text: ${responseText}`);
            })
            .catch((error) => {
                console.error(error);
            });
    }
    /* ---------------------------------------------------------------------------------------- */
    /* UP VOTE HANDLE PRESS ----------------------------------------------------------------- */
    /* ---------------------------------------------------------------------------------------- */

    
    const handleDBChanges = (update_votes) => {
        handleVotePress('votes/update', 'PUT', { // updates votes. 
            headers: {"Content-type": formContentType}, body: `cid=${props.cid}&votes=${update_votes}`});
    }

    const handlePressUpVote = () => {
      // handle press upvote button: to remove or add an upvote.
      let response = 'upvote';
      let update_votes;
      if(up[0] == 0) { // not pressed
        if (down[0] == 0) { // not down voted -- procede to upvote and add 1 to votes
            update_votes = upvote(); 
          handleVotePress('votes/add', 'POST', { // adds into votes. 
            headers: { "Content-type": formContentType }, body: `cid=${props.cid}&uid=${uid}&response=${response}`});

        } else { // down voted -- state changes: add upvote state, remove downvote, add 2
            // update_votes = rmdownvote(); // SWITCH
            // update_votes = upvote();
            // update_votes = update_votes + 1;
            update_votes = switchVote(response);

          console.log("switches to upvote: " + comVotes);

          handleVotePress('votes/switch', 'PUT', { // swtiches response in votes. 
            headers: {"Content-type": formContentType}, body: `cid=${props.cid}&uid=${uid}&response=${response}`});
 
        }
      } else { // already up voted, remove upvote
        update_votes = rmupvote();
        console.log("Removes upvote: " + comVotes);

        handleVotePress('votes/remove', 'DELETE', { // adds into votes. 
            headers: {"Content-type": formContentType}, body: `cid=${props.cid}&uid=${uid}`});
      }
      handleDBChanges(update_votes);
  }

    /* ---------------------------------------------------------------------------------------- */
    /* DOWN VOTE HANDLE PRESS ----------------------------------------------------------------- */
    /* ---------------------------------------------------------------------------------------- */

  const handlePressDownVote = () => {
    // handle press down vote button: to remove or add an downvote.
    let response = 'downvote';
    let update_votes;

    if(down[0] == 0) { // not pressed
      if (up[0] == 0) { // not up voted -- procede to downvote and subtract 1 to votes
        update_votes = downvote();

        handleVotePress('votes/add', 'POST', { // adds into votes. 
            headers: { "Content-type": formContentType }, body: `cid=${props.cid}&uid=${uid}&response=${response}`});


      } else { // up voted -- state changes: add down vote state, remove up vote, add 2
        // update_votes = rmupvote();
        // update_votes = downvote();
        // update_votes = update_votes - 1;
        update_votes = switchVote(response);

        handleVotePress('votes/switch', 'PUT', { // swtiches response in votes. 
            headers: {"Content-type": formContentType}, body: `cid=${props.cid}&uid=${uid}&response=${response}`});
      }
    } else { // already down voted, remove downvote
        update_votes = rmdownvote();

      handleVotePress('votes/remove', 'DELETE', { // adds into votes. 
        headers: {"Content-type": formContentType}, body: `cid=${props.cid}&uid=${uid}&response=${response}`});
    }
    handleDBChanges(update_votes);
  }
  
    return (
        <View style={styles.comment}>
            
            <View style={styles.itemLeft}>

                <View>
                    <Text style={{fontWeight:'bold', color: props.color}}>●
                    <Text style={{color:'black'}}>  {props.text}</Text></Text>
                </View>
            </View>
            <View style={styles.itemRight}>
                {/* <Text>🗑️</Text> */}              

                <View style={styles.date}>
                    <Text style={{paddingBottom: 10, fontSize:12,}}>{props.date} </Text>    
                    <View style={{marginTop: -20}}>
                    <Button 
                        title={trash}
                        onPress={() => deleteComment()}
                        />
                </View>     
                </View>
                <View style={styles.votes}>
                    
                    <Button 
                        title={up[2]} 
                        color={up[1]}
                        onPress={()=>{ handlePressUpVote() }}
                        />
                        <View style={{paddingTop: 12}}>
                            <Text style={{fontWeight: 'bold', fontSize: 15}}>{comVotes}</Text> 
                        </View>
                        <Button 
                        title={down[2]}
                        color={down[1]}
                        onPress={()=>{ handlePressDownVote() }}
                        />
                </View>
            </View>
        </View>
    );
}

const styles = StyleSheet.create({
    comment:{
        flexDirection: 'row',
        alignItems: 'center',
        justifyContent: 'space-between',
        padding: 15,
        marginHorizontal: -10,

        marginBottom: 10,
        backgroundColor: 'white',
        // flexWrap: 'wrap',
        // borderRadius: 10,
    },
    itemLeft:{
        flex: 4,
        flexDirection: 'column',
        alignItems: 'center', //align items according to this parent (like setting self align on each item)
        justifyContent: 'center',
        flexWrap: 'wrap'    
    },
    itemRight:{
        flex: 1,
        paddingRight:10, 
    },
    date:{
        flex: 1,
        // direction: 'rtl',
        alignItems: 'flex-end',
        flexDirection: 'row'
        // paddingBottom: 5,

    },
    votes:{
        flex: 2,
        marginLeft: -15,
        marginTop: -17,
        flexDirection: 'row',
        justifyContent: 'space-between',
    },
});

export default Comment;