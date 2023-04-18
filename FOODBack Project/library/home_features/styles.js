import {StyleSheet} from 'react-native'

export default StyleSheet.create({


    container: {
        flex: 1,
    
      },
    
      header1: {
        flex: 0,
        backgroundColor: '#cc8009',
        flexDirection: 'row-reverse',
        // justifyContent: 'center',
      },
      header2: {
        flex: 1.3,
        backgroundColor: '#cc8009',
        paddingVertical: 10,
        alignItems: 'center',
        justifyContent: 'center',
      },
    
      body: {
        flex: 20,
        // padding: 10,
        backgroundColor: 'white',
        alignItems: 'center',
        justifyContent: 'center',
        alignItems: 'stretch',
      },
    
      
      nav: {
        flex: 2.3, 
        backgroundColor: '#cc8009',
        alignItems: 'center',
        justifyContent: 'space-evenly',
        flexDirection:'row',
    
      },
      nav2: {
        flex: 0.105, 
        backgroundColor: '#cc8009',
        alignItems: 'center',
        justifyContent: 'space-evenly',
        flexDirection:'row',
    
      },
      text: {
        // padding: 10,
        fontSize: 20,
        fontWeight: 'bold',
      },
    
      section: {
        backgroundColor: '#e6e6e6',
        paddingTop: 10,
        paddingBottom: 10,
        padding: 10,
        margin: 10,
        // marginLeft: 20,
        // marginRight: 20,

      },
    
      cafView:{
        flex:10,
        backgroundColor:'orange',
      },

      progbar: {
        fontSize: 12,
        color: 'green',
      },
      progbar2: {
        fontSize: 12,
        color: 'red',
      },

    image: {
        height: '50%',
        width: '50%'
    },
    touchable: {
      alignItems: 'center',
      justifyContent: 'center'
    },

    /////// comment section

    comments: {
      padding: 10,
    },

    writeCommentWrapper: {
      position: 'absolute',
      bottom: 0,
      width: '97%',
      flexDirection: 'row',
      justifyContent: 'space-around',
      alignItems: 'center',
      backgroundColor: '#e6e6e6',
      paddingLeft: 5,
    },
    
    input:{
      paddingVertical:15,
      paddingHorizontal: 15,
      backgroundColor: '#e6e6e6',
      // borderRadius: 60,
      borderColor: '#c0c0c0',
      borderWidth: 1,
      color: 'green',
      fontWeight: 'bold',
      width: '90%',
      
    },
    addWrapper: {
      width:45.6,
      height:47.6,
      backgroundColor: '#e6e6e6',
      // borderRadius:50,
      justifyContent: 'center',
      alignItems: 'center',
      borderColor: '#c0c0c0',
      borderWidth: 1,
    },
    addText: {},

    cafHeader:{
      flex:1,
      flexDirection: 'row',
      justifyContent: 'space-between',
    },


    /// REFRESH BUTTON header
});
