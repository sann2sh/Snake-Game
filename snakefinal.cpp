#include<stdio.h> 
#include<windows.h>
#include<conio.h> 


int r=25; // Rows
int c=25; // Columns
int key; // Key pressed by user
int direction=0; // Direction of snake
int fail=0; // Game over flag
int score=0; // Player's score
int length; // Length of snake
int sec=150; // Time delay for game speed
int op=1; // Option selected in menu
char tempname[20]; // Temporary player name
char tempmonth[5]; // Temporary month
int tempday; // Temporary day
int tempyear; // Temporary year
int tempscore; // Temporary score

// Declare structure for position
struct pos{
	int x; // x-coordinate
	int y; // y-coordinate
};

// Declare array of structures for snake and fruit
struct pos snake[100]; // Snake body
struct pos fruit; // Fruit

// Declare structure for player information
struct playerinfo{
	char name[20]; // Player name
	int score; // Player score
	char month[5]; // Month of play
	int day; // Day of play
	int year; // Year of play
};

// Declare player and players array
struct playerinfo player; // Current player
struct playerinfo players[1000]; // All players



// Function prototypes
void startgame();
void menu();
void updatemenu();
int leaderboard();
void start();
void initialize();
void draw();
void stats();
void input();
void update();
void inherit();
void over();
int savegame();

// Function to initialize the game
void initialize(){
	r=25; // Reset Rows
	c=25; // Reset Columns
	direction=0; // Reset direction
	fail=0; // Reset game over flag
	score=0; // Reset score
	length=0; // Reset length
	snake[0].x=rand() % c; // Randomly position snake
	snake[0].y=rand() % r; // Randomly position snake
	fruit.x= rand() % c; // Randomly position fruit
	fruit.y=rand() % r; // Randomly position fruit
}

// Function to update the position of the snake
void inherit(){
	for(int i=length;i>0;i--){
		snake[i].x=snake[i-1].x;
		snake[i].y=snake[i-1].y;
	}
}



// Function to draw the game board
void draw(){
	system("cls"); // Clear screen
	for(int i=0;i<=(c/2)-1;i++){
		printf("> "); // Print top border
	}
	printf("Score=%d ",score); // Print score
	for(int i=(c/2)-1;i<=c-3;i++){
		printf("> "); // Print top border
	}
	printf("\n"); // New line
	for(int i=0;i<=r;i++){
		printf("X "); // Print left border
		for(int j=0;j<=c;j++){
			if(i==snake[0].y && j==snake[0].x){
				printf("* "); // Print snake head
			}
			else if(i==fruit.y && j==fruit.x){
				printf("<>"); // Print fruit
			}
			else{
				int body=0;
				for(int b=1;b<=length;b++){
					if(snake[b].y==i && snake[b].x==j){
						body=1; // Snake body found
						break;
					}
				}
				if(body==1){
					printf("0 "); // Print snake body
				}
				else{
				printf("  "); // Print empty space
				}
			}
		}
		printf("X "); // Print right border
		printf("\n"); // New line
	}
	for(int i=0;i<=c+2;i++){
		printf("< "); // Print bottom border
	}
}

// Function to print game statistics
void stats(){
	//printf("\nSX%d \t SY%d\t D%d \t FX%d \t FY%d",snake[0].x, snake[0].y,direction,fruit.x, fruit.y); // For troubleshooting
	//printf("\n Score=%d",score); // Print score
}

// Function to get user input
void input(){
	if(kbhit()) // If a key is pressed
	{
		key=getch(); // Get the key pressed
		if(key==224) // If arrow keys are pressed
		{
			key=getch();
			if(key==80){ // Down arrow
				if(direction!=1){
					direction= 2; // Set direction to down
				}
			}
			else if(key==72){ // Up arrow
				if(direction!=2){
					direction= 1; // Set direction to up
				}
			}
			else if(key==75){ // Left arrow
				if(direction!=4){
					direction= 3; // Set direction to left
				}
			}
			else if(key==77){ // Right arrow
				if(direction!=3){
					direction= 4; // Set direction to right
				}
			}
		}
		// By W,A,S,D AND NUM keys 8,4,5,6
		else if(key==87 || key==119|| key==56 ){ // W or w or 8
			if(direction!=2){
				direction= 1; // Set direction to up
			}
		}
		else if(key==83 || key==115|| key==53 ){ // S or s or 5
			if(direction!=1){
				direction= 2; // Set direction to down
			}
		}
		else if(key==65 || key==97|| key==52){ // A or a or 4
			if(direction!=4){
				direction= 3; // Set direction to left
			}
		}
		else if(key==68 || key==100|| key==54){ // D or d or 6
			if(direction!=3){
				direction= 4; // Set direction to right
			}
		}
	}
}

// Function to update the game state
void update(){
	if(direction==1){ // If direction is up
		if(snake[0].y>0){
			inherit(); // Update snake position
			snake[0].y--; // Move snake up
		}
		else{
			inherit(); // Update snake position
			snake[0].y=r; // Wrap around to bottom
		}
	}
	else if(direction==2){ // If direction is down
		if(snake[0].y<r){
			inherit(); // Update snake position
			snake[0].y++; // Move snake down
		}
		else{
			inherit(); // Update snake position
			snake[0].y=0; // Wrap around to top
		}
	}
	else if(direction==3){ // If direction is left
		if(snake[0].x>0){
			inherit(); // Update snake position
			snake[0].x--; // Move snake left
		}
		else if(snake[0].x==0){
			fail=1; // Game over if snake hits left wall
		}
	}
	else if(direction==4){ // If direction is right
		if(snake[0].x<c){
			inherit(); // Update snake position
			snake[0].x++; // Move snake right
		}
		else if(snake[0].x==c){
			fail=1; // Game over if snake hits right wall
		}
	}
	if(snake[0].x==fruit.x && snake[0].y==fruit.y){ // If snake eats fruit
		fruit.x= rand() % c; // Randomly position new fruit
		fruit.y=rand() % r; // Randomly position new fruit
		score+=10; // Increase score
		length+=1; // Increase length of snake
		if(score%20==0){ // If score is a multiple of 20
			r=r-1; // Decrease rows
			c=c-1; // Decrease columns
			sec=sec-10; // Increase game speed
			
		}
	}
	for(int b=1;b<=length;b++){ // For each segment of snake body
		if(snake[0].x==snake[b].x && snake[0].y==snake[b].y){ // If snake head hits body
			fail=1; // Game over
			break;
		}
	}
}

// Function to display leaderboard
int leaderboard(){
	FILE *file = fopen("leaderboard.txt", "r"); // Open leaderboard file
	if (file == NULL) {
		printf("Error opening file.\n");
		return 0;
	}
	int p=0;
	while(fscanf(file, "%s %d %d %s %d", &players[p].month, &players[p].day, &players[p].year, &players[p].name, &players[p].score) != EOF){ // Read player data
		p++;
	}
	for(int j=0;j<=p;j++){
		for(int k=j+1;k<=p;k++){
			if(players[j].score<players[k].score){ // If next player has higher score
				// Swap player data
				strcpy(tempname,players[j].name);
				strcpy(tempmonth,players[j].month);
				tempscore=players[j].score; // Temporary score
				tempday=players[j].day; // Temporary day
				tempyear=players[j].year; // Temporary year
				strcpy(players[j].name,players[k].name); // Swap player names
				strcpy(players[j].month,players[k].month); // Swap player months
				players[j].score=players[k].score; // Swap player scores
				players[j].day=players[k].day; // Swap player days
				players[j].year=players[k].year; // Swap player years
				strcpy(players[k].name,tempname); // Swap player names
				strcpy(players[k].month,tempmonth); // Swap player months
				players[k].score=tempscore; // Swap player scores
				players[k].day=tempday; // Swap player days
				players[k].year=tempyear; // Swap player years
			}	
		}
	}
	system("cls"); // Clear screen
	printf("               LEADERBOARD                  \n"); // Print leaderboard title
	printf("----------------------------------------------");
	printf("\n %-4s\t%-12s\t%-15s\t%-4s \n","Rank","Date","Name","Score"); // Print leaderboard header
	printf("----------------------------------------------\n");
	int rank=1; // Initialize rank
	for(int i=0;i<p;i++){ // For each player
		int copy=0;
		for(int m=0;m<i;m++){
			if(strcmp(players[i].name,players[m].name)==0){ // If player name already exists
				copy=1; // Set copy flag
				break;	
			}
		}
		if(copy==0){ // If player name does not exist
		printf(" %-4d\t%-3s %-2d %-4d\t%-15s\t%-4d \n",rank,players[i].month,players[i].day,players[i].year,players[i].name,players[i].score); // Print player rank, date, name, and score
		rank++; // Increase rank	
		}
	}
	printf("\n\n*Back - Esc*"); // Print back option
    
	while(1){ // Infinite loop
		key=getch(); // Get key pressed
		if(key==27){ // If escape key is pressed
			menu(); // Go to menu
		}
	}
}

int savegame(){ // Function to save game
	printf("\nWell played!\n"); // Print message
	FILE *file = fopen("leaderboard.txt", "a"); // Open leaderboard file in append mode
	if (file == NULL) { // If file does not exist
		printf("Error opening file.\n"); // Print error message
		return 0;
	}
	printf("Please enter your name: "); // Ask for player name
	scanf("%s", player.name); // Get player name
	player.score = score; // Set player score
	fprintf(file, "%-12s\t%-15s\t%-4d\n", __DATE__,strupr(player.name), player.score); // Write date, player name, and score to file
	fclose(file); // Close file
	printf("Game saved to leaderboard.\n"); // Print message
	printf("Thank you!"); // Print message
	printf("\n\nReplay - Press Enter\nExit   - Press Esc\nMenu   - Press M"); // Print options
	while(1){ // Infinite loop
		key=getch(); // Get key pressed
		if(key==27){ // If escape key is pressed
			exit(0); // Exit game
		}
		else if(key==13){ // If enter key is pressed
			start(); // Start game
		}
		else if(key==77 || key==109 ){ // If M or m key is pressed
			menu(); // Go to menu
		}
	}
}

void over(){ // Function to end game
	system("cls"); // Clear screen
	for(int i=0;i<=c+2;i++){
		printf("> "); // Print top border
	}
	printf("\n"); // New line
	for(int i=0;i<=r;i++){
		if(i!=r/2 && i!=((r/2)+1)){
			printf("X ");} // Print left border
		for(int j=0;j<=c;j++){
			if(i==r/2 && j==((c/2)-1)){
				printf("GAME OVER"); // Print game over message
			}
			else if(i==((r/2)+1) && j==((c/2)-1)){
				printf("Score=%d",score); // Print score
			}
			else{
				printf("  "); // Print empty space
			}
		}
		if(i!=r/2 && i!=((r/2)+1)){
			printf("X ");} // Print right border
		printf("\n"); // New line
	}
	for(int i=0;i<=c+2;i++){
		printf("< "); // Print bottom border
	}
	savegame(); // Save game
}

void start(){ // Function to start game
	int secd=15;// Initialie time delay
	int f=0; // Initialize flag
	initialize(); // Initialize game
	while(fail!=1) // While game is not over
	{
		draw(); // Draw game board
		stats(); // Print game statistics
		if(f>2){ // If flag is greater than 2
			input(); // Get user input
			update(); // Update game state
			f=0; // Reset flag
		}
		Sleep(secd); // Delay game speed
		f+=1; // Increase flag
	}		
	over(); // End game
}

void updatemenu(){ // Function to update menu
	system("cls"); // Clear screen
	printf("--------------------------------------------\n");
	printf("               Main Menu\n"); // Print menu title
	printf("--------------------------------------------\n");
	if(op==1){
		printf("--> Leaderboard\n"); // Print leaderboard option
	}
	else{
		printf("    Leaderboard\n");	
	}
	if(op==2){
		printf("--> Enter Game\n"); // Print enter game option
	}
	else{
		printf("    Enter Game\n");}
	if(op==3){
		printf("--> Exit\n\n"); // Print exit option
	}else{
		printf("    Exit\n\n");}
	printf("*Use Arrow keys and Enter key to navigate*"); // Print instructions
	printf("\n*Back - Esc*"); // Print back option
}

void menu(){ // Function to display menu
	updatemenu(); // Update menu
	while(1){ // Infinite loop
		if(kbhit()) // If a key is pressed
		{
			key=getch(); // Get the key pressed
			if(key==224) // If arrow keys are pressed
			{
				key=getch();
				if(key==80){ // Down arrow
					if(op<3){
						op++; // Increase option
						updatemenu(); // Update menu
					}
					else if(op==3){
						op=1; // Reset option
						updatemenu(); // Update menu
					}
				}
				else if(key==72){ // Up arrow
					if(op>1){
						op--; // Decrease option
						updatemenu(); // Update menu
					}
					else if(op==1){
						op=3; // Set option to last
						updatemenu(); // Update menu
					}	
				}	
			}
			else if(key==13){ // Enter key
				if(op==1){ // If leaderboard option is selected
					leaderboard(); // Display leaderboard
				}	
				else if(op==2){ // If enter game option is selected
					start(); // Start game
				}
				else if(op==3){ // If exit option is selected
					exit(0); // Exit game		
				}			
			}		
			else if(key==27){ // If escape key is pressed
				startgame(); // Start game
			}
		}
	}
}

void startgame(){ // Function to start game
	system("cls"); // Clear screen
	for(int i=0;i<=c+2;i++){
		printf("> "); // Print top border
	}
	printf("\n"); // New line
	for(int i=0;i<=(r/2)-2;i++){
		printf("X "); // Print left border
		for(int j=0;j<=c;j++){
			printf("  "); // Print empty space
		}
		printf("X "); // Print right border
		printf("\n"); // New line
	}
	printf("\n                 Welcome to Snake Game"); // Print welcome message
	printf("\n                 Press any key to Start "); // Print start instruction
	printf("\n                 Or Press M for Menu\n"); // Print menu instruction
	for(int i=(r/2)+2;i<=r;i++){
		printf("X "); // Print left border
		for(int j=0;j<=c;j++){
			printf("  "); // Print empty space
		}
		printf("X "); // Print right border
		printf("\n"); // New line
	}
	for(int i=0;i<=c+2;i++){
		printf("< "); // Print bottom border
	}
	while(1){ // Infinite loop
		if(kbhit()){ // If a key is pressed
			char k=getch(); // Get the key pressed
			if(k=='M'|| k=='m'){ // If M or m key is pressed
				menu(); // Display menu
			}
			else{
				start(); // Start game
			}
		}
	}	
}

int main(){ // Main function
	startgame(); // Start game
}

