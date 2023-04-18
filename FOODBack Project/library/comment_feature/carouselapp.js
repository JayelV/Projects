import React from 'react';
import { View, Text, StyleSheet } from 'react-native';
import Carousel2 from './components/Carousel2';

const images = [
  'https://i.imgur.com/PPw39U3.jpg',
  'https://i.imgur.com/2kHbLFO.jpg',
  'https://i.imgur.com/5hQxVZg.jpg',
  'https://i.imgur.com/qQ97QEx.jpg',
  'https://i.imgur.com/rcUWRq1.jpg'
]

export default class App extends React.Component {
  render() {
    return (
      <View style={style.container}>
        <Carousel2 images={images}/>
      </View>
    )
  }
}

const style = StyleSheet.create({
  container: {
    marginTop: 50,
  }
})