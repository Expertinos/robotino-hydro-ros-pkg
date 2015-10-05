/**
 *  Colors.cpp
 *
 *  Version: 1.0.0.0
 *  Created on: 01/10/2015
 *  Modified on: ??/10/2015
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@gmail.com)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#include "Colors.h"


/**
 *
 */
colors::ColorEnum colors::Colors::convertProductToColor(int product)
{
	colors::ColorEnum color;
	switch (product)
	{
		case 0:
			color = ORANGE; // PUCK
			break;
		case 1:
			color = YELLOW; // TV
			break;
		case 2:
			color = BLUE; // DVD
			break;
		case 3:
			color = GREEN; // CELULAR
			break;
		case 4:
			color = RED; // TABLET
			break;
		case 5:
			color = BLACK; // NOTEBOOK
			break;
		case -1: 
			color = NONE;
			break;
		default:
			color = NONE; // PUCK
	}
	return color;
}

/**
 *
 */
int colors::Colors::toProduct(colors::ColorEnum color)
{
	int product;
	switch (color)
	{
		case ORANGE: // PUCK
			product = 0;
			break;
		case YELLOW: // TV
			product = 1;
			break;
		case BLUE: // DVD
			product = 2;
			break;
		case GREEN: // CELULAR
			product = 3;
			break;
		case RED: // TABLET
			product = 4;
			break;
		case BLACK: // NOTEBOOK
			product = 5;
			break;
		default: //NONE
			product = -1;
	}
	return product;
}

/**
 *
 */
std::string colors::Colors::toString(colors::ColorEnum color)
{
	std::string color_name;
	switch (color)
	{
		case ORANGE: // PUCK
			color_name = "ORANGE";
			break;
		case YELLOW: // TV
			color_name = "YELLOW";
			break;
		case BLUE: // DVD
			color_name = "BLUE";
			break;
		case GREEN: // CELULAR
			color_name = "GREEN";
			break;
		case RED: // TABLET
			color_name = "RED";
			break;
		case BLACK: // NOTEBOOK
			color_name = "BLACK";
			break;
		default: //NONE
			color_name = "";
	}
	return color_name;
}

/**
 *
 */
std::string colors::Colors::convertProductToString(int product)
{
	std::string product_name;
	switch (product)
	{
		case 0:
			product_name = "PUCK";
			break;
		case 1:
			product_name = "TV";
			break;
		case 2:
			product_name = "DVD";
			break;
		case 3:
			product_name = "CELULAR";
			break;
		case 4:
			product_name = "TABLET";
			break;
		case 5:
			product_name = "NOTEBOOK";
			break;
		default:
			product_name = "";
	}
	return product_name;
}

/**
 *
 */
std::string colors::Colors::convertProductToString(colors::ColorEnum color)
{
	std::string product_name;
	switch (color)
	{
		case ORANGE: // PUCK
			product_name = "PUCK";
			break;
		case YELLOW: // TV
			product_name = "TV";
			break;
		case BLUE: // DVD
			product_name = "DVD";
			break;
		case GREEN: // CELULAR
			product_name = "CELULAR";
			break;
		case RED: // TABLET
			product_name = "TABLET";
			break;
		case BLACK: // NOTEBOOK
			product_name = "NOTEBOOK";
			break;
		default:
			product_name = "";
	}
	return product_name;
}
