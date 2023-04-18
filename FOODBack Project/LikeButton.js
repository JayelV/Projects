import React, { Component } from "react";
import { View, Text, Button } from 'react-native';

export default class LikeButton extends Component {
	constructor() {
		super();
		this.state = {
			liked: false
		};
		this.handlePress = this.handlePress.bind(this);
	}
	
	handlePress = () => {
		this.setState({
			liked: !this.state.liked
		});
	}
	
	render() {
		const text = this.state.liked ? 'liked' : 'haven\'t liked';
		const label = this.state.liked ? 'Like' : 'Unlike';
		return (
			<View style={{paddingTop: 100, paddingLeft: 50 }}>
				<Button onPress={() => this.handlePress()}
					title = {label} />
				<Text>you {text} this. </Text>
			</View>
		);
	}
}