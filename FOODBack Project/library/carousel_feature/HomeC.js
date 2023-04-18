import React from 'react'
import {View, Text} from 'react-native'
import Carousel from './Carousel'
import { dummyData } from './Data'


const HomeC = ({navigation}) =>{
    return (
        <View>
            <Carousel data = {dummyData}/>
        </View>
    )
}

export default HomeC;