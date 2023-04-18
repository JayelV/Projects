import React from 'react'
import {createAppContainer} from 'react-navigation'
import {createStackNavigator} from 'react-navigation-stack'

import HomeC from './HomeC' //not sure about this line

const stackNavigator = createStackNavigator({
  HomeC:HomeC
})

const AppCarousel = createAppContainer(stackNavigator)
export default AppCarousel;
