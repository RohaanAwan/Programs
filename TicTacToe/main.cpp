#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <Windows.h>

using namespace sf;

class Object: public Sprite
{
public:
	int x1;
	int y1;

	Object()
	{
		x1 = 0, y1 = 0;
	}
};

class Button : public Object
{
public:
	Sprite button_1;

	Button()
	{
		SetCoordinates();
	}
	void ApplyTexture(Texture &texture_)
	{
		button_1.setTexture(texture_);
	}
	void SetCoordinates()
	{
		x1 = button_1.getGlobalBounds().left;
		y1 = button_1.getGlobalBounds().top;

	}
	bool isButtonPressed(Vector2i position_cursor)
	{
		if ((position_cursor.x >= x1 && position_cursor.y >= y1))
		{
			return true;
		}
		else
			return false;
	}
};

void loadGame(RenderWindow &window);

void mainMenu()
{
	RenderWindow mainWindow(VideoMode(1024, 720), "MainMenu", Style::Resize);
	Texture Texture;
	Texture.loadFromFile("resources/playButton.png");
	
	Button button;
	button.button_1.setTexture(Texture);
	button.button_1.setScale(0.5, 0.5);
	button.button_1.setPosition(250, 200);

	while (mainWindow.isOpen())
	{
		Event event_;
		bool state = 1;
		while (mainWindow.pollEvent(event_))
		{
			if (event_.type == Event::Closed)
			{
				mainWindow.close();
			}

			if (button.isButtonPressed(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
			{
				loadGame(mainWindow);
				state = 0;
			}

			mainWindow.clear(Color::White);

			mainWindow.draw(button.button_1);

			mainWindow.display();

			if (state == 0)
				mainWindow.close();
		}
	}
}

void ShowMessage(RenderWindow &window, int score)
{
	Font font;
	font.loadFromFile("resources/Oswald-Regular.ttf");
	Text text;
	text.setFont(font);
	text.setCharacterSize(80);
	text.setPosition(200, 300);

	if (score == 1)
	{
		text.setString("Player 1 is the Winner");
	}
	else
	{
		text.setString("Player 2 is the Winner");
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed())
			{
				window.close();
			}

			if (score == 1)
			{
				window.clear(Color::Blue);
				window.draw(text);
				window.display();
			}
			else
			{
				window.clear(Color::Red);
				window.draw(text);
				window.display();
			}
		}

	}
}

void loadGame(RenderWindow &window)
{
	int dataSet[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} }, score_player1 = 0, score_player2 = 0;

	//sprite
	Sprite grid, icon_1, icon_2;
	//textures
	Texture gridt, icon_1t, icon_2t;

	Font font1; font1.loadFromFile("resources/Oswald-Regular.ttf"); Font font2; font2.loadFromFile("resources/Oswald-Regular.ttf");
	Text text1; text1.setFont(font1); text1.setPosition(800, 100);  Text text2; text2.setFont(font2); text2.setPosition(800, 200);

	//loading resources
	gridt.loadFromFile("resources/spritesheet.png");
	icon_1t.loadFromFile("resources/coins.png", IntRect(14, 6, 37, 23));
	icon_2t.loadFromFile("resources/coins.png", IntRect(13, 29, 37, 47));

	grid.setTexture(gridt);
	icon_1.setTexture(icon_1t);
	icon_2.setTexture(icon_2t);
	icon_1.setScale(8, 8);
	icon_2.setScale(6, 7);
	icon_2.setPosition(230, 20);

	bool turn = 0;

	while (window.isOpen())
	{
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

		}
	
		float x = 10, y = 10;
		Sprite sprites[3][3];

		for (int i = 0; i < 3; i++)
		{

			for (int j = 0; j < 3; j++)
			{
				if (dataSet[i][j] == 1)
				{
					sprites[i][j].setTexture(icon_1t);
					sprites[i][j].setScale(7, 7);
					sprites[i][j].setPosition(x, y);
				}
				else if (dataSet[i][j] == 2)
				{
					sprites[i][j].setTexture(icon_2t);
					sprites[i][j].setScale(6, 7);
					sprites[i][j].setPosition(x, y);
					;
				}
				x += 220;
			}
			y += 220;
			x = 0;
		}
		Sleep(100);

		if(!turn)
		{
			srand(time(0));
			int X = rand() % 3, Y = rand() % 3;

			Jump:
			if (dataSet[X][Y] == 0)
			{
				dataSet[X][Y] = 2;
			}
			else
			{
				X = rand() % 3, Y = rand() % 3;
				if (dataSet[X][Y] == 0)
					dataSet[X][Y] = 2;
				else
					goto Jump;
			}
			turn = 1;
		}

		window.clear(Color::Black);

		window.draw(grid); window.draw(text1); window.draw(text2);

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				window.draw(sprites[i][j]);
			}
		}
		
		window.display();

		if (Mouse::isButtonPressed(Mouse::Left) && turn == 1)
		{
			int x_ = Mouse::getPosition().x, y_ = Mouse::getPosition().y;

			if ((x_ >= 460 && y_ >= 226) && (x_ <= 645 && y_ <= 406))
			{
				if (dataSet[0][0] == 0)
				{
					dataSet[0][0] = 1;
					turn = 0;
				}
			}
			else if ((x_ >= 691 && y >= 234) && (x_ <= 829 && y_ <= 413))
			{
				if (dataSet[0][1] == 0)
				{
					dataSet[0][1] = 1;
					turn = 0;
				}
			}
			else if ((x_ >= 875 && y_ >= 233) && (x_ <= 1040 && y_ <= 409))
			{
				if (dataSet[0][2] == 0)
				{
					dataSet[0][2] = 1;
					turn = 0;
				}
			}
			else if ((x_ >= 460 && y_ >= 461) && (x_ <= 645 && y_ <= 604))
			{
				if (dataSet[1][0] == 0)
				{
					dataSet[1][0] = 1;
					turn = 0;
				}
			}
			else if ((x_ >= 691 && y_ >= 461) && (x_ <= 829 && y_ <= 604))
			{
				if (dataSet[1][1] == 0)
				{
					dataSet[1][1] = 1;
					turn = 0;
				}
			}
			else if ((x_ >= 875 && y_ >= 461) && (x_ <= 1040 && y_ <= 604))
			{
				if (dataSet[1][2] == 0)
				{
					dataSet[1][2] = 1;
					turn = 0;
				}
			}
			else if ((x_ >= 460 && y_ >= 646) && (x_ <= 645 && y_ <= 810))
			{
				if (dataSet[2][0] == 0)
				{
					dataSet[2][0] = 1;
					turn = 0;
				}
			}
			else if ((x_ >= 691 && y_ >= 646) && (x_ <= 829 && y_ <= 810))
			{
				if (dataSet[2][1] == 0)
				{
					dataSet[2][1] = 1;
					turn = 0;
				}
			}
			else if ((x_ >= 870 && y_ >= 644) && (x_ <= 1040 && y_ <= 808))
			{
				if (dataSet[2][2] == 0)
				{
					dataSet[2][2] = 1;
					turn = 0;
				}
			}
			else
			{
				//
			}
		}

		//score loop
		for (int i = 0; i < 3; i++)
		{
			if (dataSet[i][0] == dataSet[i][1] && dataSet[i][0] == dataSet[i][2] && dataSet[i][0] == 1)
			{
				score_player1 += 1;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						window.draw(sprites[i][j]);
						dataSet[i][j] = 0;
					}
				}
			}
			else if ((dataSet[0][i] == dataSet[1][i] && dataSet[1][i] == dataSet[2][i] && dataSet[1][i] == 1))
			{
				score_player1 += 1;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						dataSet[i][j] = 0;
					}
				}
			}
			else if ((dataSet[0][0] == dataSet[1][1] && dataSet[2][2] == dataSet[1][1] && dataSet[1][1] == 1) || (dataSet[0][2] == dataSet[1][1] && dataSet[1][1] == dataSet[2][0] && dataSet[2][0] == 1))
			{
				score_player1 += 1;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						dataSet[i][j] = 0;
					}
				}

			}

			else if (dataSet[i][0] == dataSet[i][1] && dataSet[i][0] == dataSet[i][2] && dataSet[i][0] == 2)
			{
				score_player2 += 1;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						dataSet[i][j] = 0;
					}
				}
				
			}
			else if ((dataSet[0][i] == dataSet[1][i] && dataSet[1][i] == dataSet[2][i] && dataSet[1][i] == 2))
			{
				score_player2 += 1;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						dataSet[i][j] = 0;
					}
				}
				
			}
			else if ((dataSet[0][0] == dataSet[1][1] && dataSet[2][2] == dataSet[1][1] && dataSet[1][1] == 2) || (dataSet[0][2] == dataSet[1][1] && dataSet[1][1] == dataSet[2][0] && dataSet[2][0] == 2))
			{
				score_player2 += 1;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						dataSet[i][j] = 0;
					}
				}
				
			}
		}

		int winner = 0;

		if (score_player1 == 4)
		{
			winner = 1;
		}
		else if (score_player2 == 4)
		{
			winner = 2;
		}

		switch (winner)
		{
		case 1:
			Sleep(1000);
			ShowMessage(window, 1);
			break;
		case 2:
			Sleep(1000);
			ShowMessage(window, 2);
			break;
		}

		switch (score_player1)
		{
		case 0:
			text1.setString("Player1: 0");
			break;
		case 1:
			text1.setString("Player1: 1");
			break;
		case 2:
			text1.setString("Player1: 2");
			break;
		case 3:
			text1.setString("Player1: 3");
			break;
		case 4:
			text1.setString("Player1: 4");
			break;
		}

		switch (score_player2)
		{
		case 0:
			text2.setString("Player2: 0");
			break;
		case 1:
			text2.setString("Player2: 1");
			break;
		case 2:
			text2.setString("Player2: 2");
			break;
		case 3:
			text2.setString("Player2: 3");
			break;
		case 4:
			text2.setString("Player2: 4");
			break;
		}
	}
}

int main()
{
	mainMenu();
}