#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

int main(){
    sf::RenderWindow renderWindow(sf::VideoMode({800, 600}), "My window");
    std::cout<<"Hello World\n"<<std::endl;
}