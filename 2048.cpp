#include <bits/stdc++.h>

#include <conio.h>

using namespace std;
/*declaring controls of keyboard using ascii global variables*/
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class game;

class Functions{
	/*declaring controls of game*/
	char controls;
	int response;
	int state;
	char controls_array; //arrows
public:
	/*declaring controls of scores*/
	int max;
	int current_s;
	int final_score;
	int put;
	int game_matrix[4][4]; //game grid
	int saved_matrix[4][4];
	Functions():
		current_s(0),
		final_score(2048),
		put(0),
		max(0),
		response(0),
		state(1)
		{
		}
	/*functions to control game*/
	void flow(game*);
	void game_end(game*);
	void controls_read();
	void start_game_matrix();
	void update_game_matrix();
	void fill_space();
	void make_numbers();
	void highest_number();
	void backup_grid();
  
	int out_of_space();
	int movement();
};
class game : public Functions
{
	char option;

public:
	/*functions to display*/
	void display_matrix();
	void display_win();
	void display_loser();
	char save_screen();
	char retry_screen(int);
};


void Functions::controls_read(){
	/*reader of keyboard controls*/
	controls_array = _getch();
}

void Functions::flow(game *game)
{
	/*switch statement to control the flow of the game*/
	switch(controls_array){
		case 72:
		case 80:
		case 75:
		case 77:
			game->backup_grid();
			game->fill_space();
			game->update_game_matrix();
			game->fill_space();
			game->highest_number();
			game->display_matrix();
	
			if(game->out_of_space()&&state){
				response=-1;
				break;
			}
			else if(game->movement()){
				game->make_numbers();
				break;
			}else{
				response=0;	
				break;
			}
			/*saving the game*/
		case 'S':{
			std::ofstream ofs;
			ofs.open("load_game_later.txt", std::ofstream::out | std::ofstream::trunc);
			ofs.close();
			fstream loadgame;
			loadgame.open ("load_game_later.txt");
			if(!loadgame){
				std::ofstream outfile ("load_game_later.txt");
				outfile.close();
			}
			loadgame<<1<<"\n";
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++){
					loadgame<<game_matrix[i][j]<<" ";
				}
				loadgame<<"\n";
			}
			loadgame<<max;
			loadgame<<"\n";
			loadgame<<current_s;
			response=11;
			loadgame.close();
			break;
		}
		/**loading the saved game*/
		case 'R': 	{
			fstream loadgame;
			loadgame.open ("load_game_later.txt");
			if(!loadgame){
				std::ofstream outfile ("load_game_later.txt");
				outfile.close();
			}
			loadgame<<0<<"\n";
			loadgame.close();		
			game->start_game_matrix();
			current_s=0;
			put=0;
			break;
		}
		/**quitiing the game*/
		case 'Q':{
			fstream loadgame;
			loadgame.open ("load_game_later.txt");
			if(!loadgame){
				std::ofstream outfile ("load_game_later.txt");
				outfile.close();
			}
			loadgame<<0<<"\n";
			loadgame.close();		
			response=12;
			break;
		}
		case 's':{
			std::ofstream ofs;
			ofs.open("load_game_later.txt", std::ofstream::out | std::ofstream::trunc);
			ofs.close();
			fstream loadgame;
			loadgame.open ("load_game_later.txt");
			if(!loadgame){
				std::ofstream outfile ("load_game_later.txt");
				outfile.close();
			}
			loadgame<<1<<"\n";
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++){
					loadgame<<game_matrix[i][j]<<" ";
				}
				loadgame<<"\n";
			}
			loadgame<<max;
			loadgame<<"\n";
			loadgame<<current_s;
			response=11;
			loadgame.close();
			break;
		}
		case 'r': 	{
			fstream loadgame;
			loadgame.open ("load_game_later.txt");
			if(!loadgame){
				std::ofstream outfile ("load_game_later.txt");
				outfile.close();
			}
			loadgame<<0<<"\n";
			loadgame.close();		
			game->start_game_matrix();
			current_s=0;
			put=0;
			break;
		}
		case 'q':{
			fstream loadgame;
			loadgame.open ("load_game_later.txt");
			if(!loadgame){
				std::ofstream outfile ("load_game_later.txt");
				outfile.close();
			}
			loadgame<<0<<"\n";
			loadgame.close();		
			response=12;
			break;
		}		  
	}
}
/**ending the game and saving it*/
void Functions::game_end(game *display){
	if(max==final_score){
		display->display_win();
		if(display->retry_screen(0)=='n'){
			response=-1;
		}else{
			final_score*=2;
		}
	}else if(response==-1){
		display->display_loser();
		if(display->retry_screen(1)=='y'){
			display->start_game_matrix();
			response=0;
		}
	}else if(response==11){
		display->save_screen();
		response=-1;
	}else if(response==12){
		display->display_loser();
		response = -1;
	}
    
	if(response==-1){
		cout<<"\n\n\n\n\t\tGoodbye! Press any key to close the game!\n";
		getchar();
		exit(0);
	}
}
int random_index(int x){
    int index;
    index=rand()%x+0;
	return index;
}
/**function to start the game*/
void Functions::start_game_matrix(){
	fstream loadgame;
	loadgame.open ("load_game_later.txt");
	/*if user do not save the game it drops*/
	if(!loadgame){
		std::ofstream outfile ("load_game_later.txt");
		outfile.close();
	}
	int file_input;
	loadgame>>file_input;
	int i,j;
	put=0;
	current_s=0;
	max=0;
	if(file_input==1){
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				loadgame>>game_matrix[i][j];
			}
		}
		while(loadgame){
			loadgame>>max;
			loadgame>>current_s;
		}	
	}else{
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				game_matrix[i][j]=0;
			}
		}	
		i=random_index(4);
		j=random_index(4);
		game_matrix[i][j]=2;
		i=random_index(4);
		j=random_index(4);
		game_matrix[i][j]=2;
	}
	
	loadgame.close();
}
/*display the user interface*/
void game::display_matrix(){
	system("cls");
	cout<<"2048"<<"\n\n";
	cout<<"SCORE:"<<current_s<<" \n\n\n\n";
		for(int i=0;i<4;i++){
			cout<<"\t\t     |";
			for(int j=0;j<4;j++){
				if(game_matrix[i][j]){
					printf("%4d    |",game_matrix[i][j]);
				}else{
					printf("%4c    |",' ');	
				}
			}
			cout<<"\n\n";
		}
		cout<<"Control Keys:"<<"\n\n";
		cout<<"(Up-Arrow)\t\t\tUp"<<"\n";
		cout<<"(Down-Arrow)\t\t\tDown"<<"\n";
		cout<<"(Right-Arrow)\t\t\tRight"<<"\n";
		cout<<"(Left-Arrow)\t\t\tLeft"<<"\n";
		cout<<"R\t\t\t\tRestart"<<"\n";
		cout<<"S\t\t\t\tSave"<<"\n";
		cout<<"Q\t\t\t\tQuit"<<"\n";  
}
/**backup the matrix of the game*/
void Functions::backup_grid(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			saved_matrix[i][j]=game_matrix[i][j];
		}
	}			
}
/*nested loops to fill the space*/
void Functions::fill_space(){
        if(controls_array==72){
			for(int i=0;i<4;i++)
				for(int j=0;j<4;j++){
					if(!game_matrix[j][i]){
						for(int k=j+1;k<4;k++)
							if(game_matrix[k][i]){
								game_matrix[j][i]=game_matrix[k][i];
								game_matrix[k][i]=0;
								break;
							}
					}

				}

		}else if(controls_array==80){
			for(int i=0;i<4;i++)
				for(int j=3;j>=0;j--){
					if(!game_matrix[j][i]){
						for(int k=j-1;k>=0;k--)
							if(game_matrix[k][i]){
								game_matrix[j][i]=game_matrix[k][i];
								game_matrix[k][i]=0;
								break;
							}
						}
				}

		}else if(controls_array==75){
			for(int i=0;i<4;i++)
				for(int j=0;j<4;j++){
					if(!game_matrix[i][j]){
						for(int k=j+1;k<4;k++)
							if(game_matrix[i][k]){
								game_matrix[i][j]=game_matrix[i][k];
								game_matrix[i][k]=0;
								break;
							}
					}
				}

		}else if(controls_array==77){
			for(int i=0;i<4;i++)
				for(int j=3;j>=0;j--){
					if(!game_matrix[i][j]){
						for(int k=j-1;k>=0;k--)
							if(game_matrix[i][k]){
								game_matrix[i][j]=game_matrix[i][k];
								game_matrix[i][k]=0;
								break;
							}
					}
				}

		}
}
/*after the game was lost*/
char game::retry_screen(int lose){	
	if(lose){
		cout<<"\n\n\n\t    > Try again? (Y/N) :: ";
	}else{
		cout<<"\n\n\n\t    > Continue? (Y/N)  :: ";
	}
	cin>>option;
	return option;
}
/**after the game was saved function*/
char game::save_screen(){	
	cout<<"\n\n\n\t    > Game saved! ";
	return 15;
}
/**update function when cliked the arrows*/
void Functions::update_game_matrix(){
	put=0;
	state=1;
	/**up arrow*/
        if(controls_array==72){
					for(int i=0;i<4;i++)
						for(int j=0;j<3;j++)
						{
							if(game_matrix[j][i]&&game_matrix[j][i]==game_matrix[j+1][i])
							{
								state=0;
								game_matrix[j][i]+=game_matrix[j+1][i];
								game_matrix[j+1][i]=0;
								put+=(((log2(game_matrix[j][i]))-1)*game_matrix[j][i]);
								current_s+=(((log2(game_matrix[j][i]))-1)*game_matrix[j][i]);
								
							}
						}
		}
		/**down arrow*/
		else if(controls_array==80){
					for(int i=0;i<4;i++)
						for(int j=3;j>0;j--)
						{
							if(game_matrix[j][i]&&game_matrix[j][i]==game_matrix[j-1][i])
							{
								state=0;
								game_matrix[j][i]+=game_matrix[j-1][i];
								game_matrix[j-1][i]=0;
								put+=(((log2(game_matrix[j][i]))-1)*game_matrix[j][i]);
								current_s+=(((log2(game_matrix[j][i]))-1)*game_matrix[j][i]);
							}
						}
		}
		/**right arrow*/
		else if(controls_array==75){
					for(int i=0;i<4;i++)
						for(int j=0;j<3;j++)
						{
							if(game_matrix[i][j]&&game_matrix[i][j]==game_matrix[i][j+1])
							{
								state=0;
								game_matrix[i][j]+=game_matrix[i][j+1];
								game_matrix[i][j+1]=0;
								put+=((log2(game_matrix[i][j]))-1)*game_matrix[i][j];
								current_s+=((log2(game_matrix[i][j]))-1)*game_matrix[i][j];
							}
						}
		}
		/**left arrow*/
		else  if(controls_array==77){
					for(int i=0;i<4;i++)
						for(int j=3;j>0;j--)
						{
							if(game_matrix[i][j]&&game_matrix[i][j]==game_matrix[i][j-1])
							{
								state=0;
								game_matrix[i][j]+=game_matrix[i][j-1];
								game_matrix[i][j-1]=0;
								put+=((log2(game_matrix[i][j]))-1)*game_matrix[i][j];
								current_s+=(((log2(game_matrix[i][j]))-1)*game_matrix[i][j]);
							}
						}
		}
	
	

}
/**making first numbers*/
void Functions::make_numbers()
{
		int i,j,k;
		
		do
		{
		    i=random_index(4);
		    j=random_index(4);
		    k=random_index(10);

		}while(game_matrix[i][j]);
				
		
			
		if(k<2)
		    game_matrix[i][j]=4;

		else
		    game_matrix[i][j]=2;
	

}
		
/**highest score*/
void Functions::highest_number()
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(game_matrix[i][j]>max)
				max=game_matrix[i][j];
}
/**out of matrix*/
int Functions::out_of_space()
{
	int k=1;

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			if(!game_matrix[i][j])
				k=0;
				
		}
return k;
}
/**movement of the player*/
int Functions::movement()
{
	int k=0;

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(saved_matrix[i][j]!=game_matrix[i][j])
			{	
				k=1;
				break;
			}
return k;
}
/**winner display*/
void game::display_win()
{
	system("cls");
	
	cout<<endl<<endl;
	cout<<"\n\n\n\n\t\t\t Highest score\t     SCORE\t ";
	printf("\n\n\t\t\t %4d\t    %12d\t    ",max,current_s);

}
/**display loser*/
void game::display_loser()
{
	system("cls");
	cout<<"\n\n\n\n\t\t\t Highest score\t     SCORE\t ";
	printf("\n\n\t\t\t %4d\t    %12d\t    ",max,current_s);

}


/**main function to call all neccesary functions*/
int main(){
	game game;
	srand(time(0));
	game.start_game_matrix();
	while(true){
		game.display_matrix();
		game.controls_read();
		game.flow(&game);
		game.game_end(&game);
    };
	return 0;
}
