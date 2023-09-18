#include "dynamixel.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void move_to_location(int connection, unsigned char id,
			unsigned char loc_h, unsigned char loc_l) {

	unsigned char cs = ~ ( id + 0x07 + 0x03 + 0x1e + loc_l + loc_h + 
				0x30 + 0x00);

	unsigned char arr[] = { 0xff, 0xff, id, 0x07, 0x03, 0x1e, loc_l,
                                       loc_h,0x30, 0x00, cs };

	int buff_len = 100;
	unsigned char buff[buff_len];

	int bytes_read = write_to_connection(connection,arr,14,buff,buff_len);

}

void wait_until_done(int connection, unsigned char id) {
	usleep(900000);
}

void grab(int connection){  //This function clasps the fifth motor in order to grab blocks
	move_to_location(connection, 5, 0x01, 0x3e);
}
void letGo(int connection){  //This function unclasps the fifth motor to drop blocks
	move_to_location(connection, 5, 0x01, 0xB8);
	wait_until_done(connection, 5);

}
void lift(int connection){ //This function lifts the robot Arm using the second motor, and then has a small delay.
	move_to_location(connection, 2, 0x01, 0x5E);
	wait_until_done(connection, 2);

}
void topBlock(int connection, int locH, int locL, int Grab){//This function grabs/drops a block on the top of a selected location
	move_to_location(connection,1,locH,locL);  //Rotation
	wait_until_done(connection, 1);
	move_to_location(connection,2,0x01,0x36);
	move_to_location(connection,3,0x01,0x94);
	move_to_location(connection,4,0x00,0xEB);
	wait_until_done(connection, 4);
	if(Grab == 0){
		grab(connection);
	}else{
		letGo(connection);
	}
	wait_until_done(connection, 5);
}
void bottomBlock(int connection, int locH, int locL, int Grab){//This function grabs/drops a block on the bottom of a selected location
	move_to_location(connection,1,locH,locL);  //Rotation
	wait_until_done(connection, 1);
	move_to_location(connection,2,0x01,0x0E);
	move_to_location(connection,3,0x01,0x80);
	move_to_location(connection,4,0x01,0x22);
	wait_until_done(connection, 4);



	if(Grab == 0){
		grab(connection);
	}else{
		letGo(connection);
	}
	wait_until_done(connection, 5);
}
void middleBlock(int connection, int locH, int locL, int Grab){  //This function grabs/drops a block in the middle of a selected location
	move_to_location(connection,1,locH,locL);  //Rotation
	wait_until_done(connection, 1);
	move_to_location(connection,2,0x01,0x22);
	move_to_location(connection,3,0x01,0x8A);
	move_to_location(connection,4,0x01,0x07);
	wait_until_done(connection, 4);
	if(Grab == 0){
		grab(connection);
	}else{
		letGo(connection);
	}
	wait_until_done(connection, 5);
}
//This function places the first block in its initial position
void initialLoc(int connection){
	grab(connection);
	lift(connection);
	bottomBlock(connection,0x01, 0xC2, 1); //Middle
	wait_until_done(connection, 3);
	wait_until_done(connection, 2);
	lift(connection);
}
//This lifts two blocks from the left
void liftTwo(int connection){
	move_to_location(connection, 4, 0x01, 0xFF);
	wait_until_done(connection, 5);
	move_to_location(connection, 2, 0x01, 0x5E);
	wait_until_done(connection, 2);
}
/*
-----------
Main Towers of Hanoi Solution

This solution completes the puzzle in seven steps, from left to right Between each movement, the robot lifts and waits a 
small amount of time to avoid collisions with other blocks.
-----------
*/
void towersOfHanoi(int connection){

	topBlock(connection,0x01, 0xC2, 0);//Top left
	lift(connection);
	bottomBlock(connection,0x02, 0x3E, 1); //Bottom Right

	lift(connection);

	middleBlock(connection,0x01, 0xC2, 0); //Middle Left 
	lift(connection);
	bottomBlock(connection,0x01, 0xFF, 1); //Bottom Middle

	lift(connection);

    bottomBlock(connection,0x02, 0x3E, 0); //Bottom Right
	lift(connection);
	middleBlock(connection,0x01, 0xFF, 1); //Middle Middle

	lift(connection);

	bottomBlock(connection,0x01, 0xC2, 0); //Bottom Left
	lift(connection);
	bottomBlock(connection,0x02, 0x3E, 1); //Bottom Right

	lift(connection);

	middleBlock(connection,0x01, 0xFF, 0); //Middle Middle
	lift(connection);
	bottomBlock(connection,0x01, 0xC2, 1); //Bottom Left

	lift(connection);

	bottomBlock(connection,0x01, 0xFF, 0); //Bottom Middle
	lift(connection);
	middleBlock(connection,0x02, 0x3E, 1); //Middle Right

	lift(connection);

	bottomBlock(connection,0x01, 0xC2, 0); //Bottom Left
	lift(connection);
	topBlock(connection,0x02, 0x3E, 1); //Top Right

	lift(connection);
}
void grabTwo(int connection, int locH, int locL, int Grab){
	move_to_location(connection,1,locH,locL);  //Rotation
	wait_until_done(connection, 1);
	move_to_location(connection,2,0x01,0x0E);
	wait_until_done(connection, 2);
	move_to_location(connection,3,0x01,0x80);
	wait_until_done(connection, 3);
	move_to_location(connection,4,0x01,0x22);
	wait_until_done(connection, 4);
	if(Grab == 0){
	move_to_location(connection, 5, 0x01, 0x20);
	}else{
		letGo(connection);
	}
	wait_until_done(connection, 5);
	lift(connection);
}
void straight(int connection, int locH, int locL){
	move_to_location(connection,1,locH,locL);  //Rotation
	move_to_location(connection,2,0x00,0x50);
	move_to_location(connection,3,0x02,0x2F);
	move_to_location(connection,4,0x02,0x40);
	wait_until_done(connection, 4);
	wait_until_done(connection, 3);
	wait_until_done(connection, 2);


}
void grabPlaced(int connection){
	move_to_location(connection,1,0x01,0xC2);  //Rotation
	move_to_location(connection,3,0x02,0x30);
	move_to_location(connection,2,0x00,0xDF);


}

int main(int argc, char* argv[]) {

	int connection = open_connection("/dev/ttyUSB0",B1000000);

	//places the block in the correct starting position
	//--------------------------------------------------
 	//initialLoc(connection);
	//--------------------------------------------------
	towersOfHanoi(connection);

	return 0;

}
