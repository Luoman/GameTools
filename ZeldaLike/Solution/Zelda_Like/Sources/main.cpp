#include <SFML/Graphics.hpp>

#include	"Renderer.hh"

#if	_DEBUG
int main()
#else
int			WinMain()
#endif
{
	Renderer *render = new Renderer();
	render->init();
	render->run();

	return (0);
}

//#include	<SFML/Graphics.hpp>
//#include	<SFML/Audio.hpp>
//#include	<iomanip>
//#include	<iostream>

//#include	"Personnage.hh"

//int		main()
//{
//	POINT Ecran = {GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)} ;
//	Ecran.x = 800; Ecran.y = 600;
//	
//	std::cout << Ecran.x << " " << Ecran.y << std::endl;
//	sf::RenderWindow App(sf::VideoMode(Ecran.x, Ecran.y, 32), "SFML Graphics");
//	//App.Create(sf::VideoMode::GetMode(0), "SFML Window", sf::Style::Fullscreen);
//
//	sf::Music Music;
//	if (!Music.OpenFromFile("Ressources/Musics/theme3.ogg"))
//		return EXIT_FAILURE;
//	//Music.Play();
//	//Music.SetLoop(true);
//
//	sf::Image Image;
//	if (!Image.LoadFromFile("Ressources/Pictures/Link.png"))
//		return EXIT_FAILURE;
//
//	sf::Image Map;
//	if (!Map.LoadFromFile("Ressources/Pictures/map1.png"))
//		return EXIT_FAILURE;
//	sf::Sprite Map1(Map);
//	Map1.SetScale(Ecran.x / 560.f, Ecran.y / 350.f);
//	//Map1.SetPosition(Ecran.x / 11.f, Ecran.y / 14.f);
//
//	Personnage *Link = new Personnage("Link", Image, 11, 8);
//
//	sf::Clock Clock;
//	sf::Event Event;
//	float ElapsedTime; 
//
//	while (App.IsOpened())
//	{
//		while (App.GetEvent(Event))
//		{
//			if (Event.Type == sf::Event::Closed)
//				App.Close();
//			if (Event.Type == sf::Event::KeyPressed)
//			{
//				if (Event.Key.Code == sf::Key::Escape)
//					App.Close();
//			}
//		}
//		ElapsedTime = App.GetFrameTime();
//		Link->control(App.GetInput(), ElapsedTime);
//		Link->animate(Clock);
//		Link->setApparence();
//		App.Clear();
//		App.Draw(Map1);
//		Link->draw(&App);
//		//App.Draw(Link->getApparence());
//		App.Display();
//		//std::cout << Link->getPosition().x << " " << Link->getPosition().y << std::endl;
//	}
//	delete Link;
//	return EXIT_SUCCESS;
//}
