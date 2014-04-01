#include"param_name.h"
#include"VectorOps.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
using namespace sf;
int param_name_obstacleMan::LHMCountdown=DEFAULT_LHMCountdown;
float param_name_obstacleMan::MIN_PING_DIST=RAFT_VISIBILITY_RADIUS*1.0f/1000.0f;
bool param_name_obstacleMan::hugsLand=false;
float param_name_obstacleMan::OBSTACLEMAN_DISP_ANGLE = PI / 1.5f;
int param_name_cannon::gameCounter=1;
Vector2f param_name_explorer::explorePoint(InformationProvider *info)
{
	int location=chooseLocation(info);
	Vector2i x=Vector2i((int)queue[location].x,(int)queue[location].y);
	if(info->pointFallsInRaftVisibleRegion(queue[location])==true) 
	{
			check[location]=1;
	}
	if(check[7]==1)
	{
		for(int i=0;i<8;i++) check[i]=0;
	}
	return queue[location];
}

void param_name_explorer::blacklistExplore(InformationProvider *info,Vector2f blacklist)
{
	int i;
	for(i=0;i<8;i++)
	{
		if(queue[i]==blacklist)
		{
			queue[i]=NULL_POS;
			check[i]=1;
		}
	}
}
int param_name_explorer::chooseLocation(InformationProvider *info)
{
	int i;
	for(i=0;i<8;i++)
	{
		if(queue[i]==NULL_POS) 
		{
				check[i]=1;
				continue;
		}
		if(check[i]==0) break; 
	}
	return i;
}
void param_name_explorer::chooseQueueOrder(InformationProvider *info)
{
	Vector2f tempQueue[8],currentR=info->getRaftPosition();
	int sector;
	queue[0] = sf::Vector2f(2.0f*RAFT_RADIUS,2.0f*RAFT_RADIUS);
	queue[1] = sf::Vector2f(info->getMapWidth()/3,2.0f*RAFT_RADIUS);
	queue[2] = sf::Vector2f(2*info->getMapWidth()/3,2.0f*2.0*RAFT_RADIUS);
	queue[3] = sf::Vector2f(info->getMapWidth()-2.0f*RAFT_RADIUS,2.0f*RAFT_RADIUS);
	queue[4] = sf::Vector2f(info->getMapWidth()-2.0f*RAFT_RADIUS,info->getMapHeight()-2.0f*RAFT_RADIUS);
	queue[5] = sf::Vector2f(2*info->getMapWidth()/3,info->getMapHeight()-2.0*RAFT_RADIUS);
	queue[6] = sf::Vector2f(info->getMapWidth()/3,info->getMapHeight()-2.0*RAFT_RADIUS);
	queue[7] = sf::Vector2f(2.0f*RAFT_RADIUS,info->getMapHeight()-2.0f*RAFT_RADIUS);
	
	if (currentR.x<1366/2&&currentR.y<768/2) sector=0;
	else if(currentR.x>1366/2&&currentR.y<768/2) sector=1;
	else if(currentR.x<1366/2&&currentR.y>768/2) sector=3;
	else sector = 2;
	if(sector==0)
	{
		tempQueue[0]=queue[0];
		tempQueue[1]=queue[1];
		tempQueue[2]=queue[5];
		tempQueue[3]=queue[4];
		tempQueue[4]=queue[3];
		tempQueue[5]=queue[2];
		tempQueue[6]=queue[6];
		tempQueue[7]=queue[7];
	}
	else if(sector==3)
	{
		tempQueue[0]=queue[7];
		tempQueue[1]=queue[0];
		tempQueue[2]=queue[1];
		tempQueue[3]=queue[5];
		tempQueue[4]=queue[4];
		tempQueue[5]=queue[3];
		tempQueue[6]=queue[2];
		tempQueue[7]=queue[6];
	}
	else if(sector==1)
	{
	
		tempQueue[0]=queue[3];
		tempQueue[1]=queue[2];
		tempQueue[2]=queue[6];
		tempQueue[3]=queue[7];
		tempQueue[4]=queue[0];
		tempQueue[5]=queue[1];
		tempQueue[6]=queue[5];
		tempQueue[7]=queue[4];
	}
	else 
	{
		tempQueue[0]=queue[4];
		tempQueue[1]=queue[3];
		tempQueue[2]=queue[2];
		tempQueue[3]=queue[6];
		tempQueue[4]=queue[7];
		tempQueue[5]=queue[0];
		tempQueue[6]=queue[1];
		tempQueue[7]=queue[5];
	}
	for(int i=0;i<8;i++)
	{
		queue[i]=tempQueue[i];
		////inputFile<<"queue "<<queue[i].x<<"i + "<<queue[i].y<<"j  aaaaaaaaaaaaaaaaaaa\n";
	}
}
void param_name::motorFunction(sf::Vector2f rFinal,InformationProvider *info, bool needWarpSpeed){
	Vector2f thrust = Vector2f(0,0);
	bool brakeApplied = false;

	/*
	float VELOCITY_THRESHOLD1 = 200.0f;
	float VELOCITY_THRESHOLD2 = 300.0f;
	float VELOCITY_THRESHOLD3 = 300.0f;
	if(VectorOps::Normalise(info->getRaftVelocity()) != VectorOps::Normalise(rFinal-info->getRaftPosition())){
		if(VectorOps::Magnitude(info->getRaftVelocity())>VELOCITY_THRESHOLD1){
			brakeApplied=true;
		}
		else{
			brakeApplied=false;
			thrust=VectorOps::Normalise(rFinal-info->getRaftPosition());
		}
	}
	else{
		if(VectorOps::Magnitude(info->getRaftVelocity())>VELOCITY_THRESHOLD2){
			//brakeApplied=true;
		}
		if(VectorOps::Magnitude(info->getRaftVelocity())<VELOCITY_THRESHOLD3){
			thrust=VectorOps::Normalise(rFinal-info->getRaftPosition());
			brakeApplied=false;
		}
	}
	*/
	/*float VELOCITY_THRESHOLD = 60.0f;
	if(VectorOps::Magnitude(info->getRaftVelocity()) > VELOCITY_THRESHOLD) {
		brakeApplied = true;
		//thrust = -VectorOps::Normalise(info->getRaftVelocity());
	} else {
		thrust = VectorOps::Normalise(rFinal - info->getRaftPosition());
		thrust *= VectorOps::Dot(VectorOps::Normalise(rFinal), VectorOps::Normalise(info->getRaftPosition()));
		brakeApplied = false;
	}
	*/
	//thrust = VectorOps::Normalise(rFinal - info->getRaftPosition()) / 2.0f;
	
	if(info->getRaftPosition() == rFinal){
		thrust = Vector2f(0,0);
		brakeApplied = true;
	} else {
		float DIRECTION_THRESHOLD = 0.6f;
		float dotProduct = VectorOps::Dot(VectorOps::Normalise(rFinal - info->getRaftPosition()), VectorOps::Normalise(info->getRaftVelocity()));
		if(dotProduct >= DIRECTION_THRESHOLD || VectorOps::Magnitude(info->getRaftVelocity()) <= 65) {
			thrust = VectorOps::Normalise(rFinal - info->getRaftPosition());
			//printf("Thrust = %fi + %fj\n", thrust.x, thrust.y);
			brakeApplied = false;
		} else {
			brakeApplied = true;
		}
	}
	// Cruise Control
	if(VectorOps::Magnitude(info->getRaftVelocity()) > 95 && !needWarpSpeed)	brakeApplied  = true;
	movementControls.brakeApplied=brakeApplied;
	movementControls.thrustVector=thrust;
}
void param_name_obstacleMan::setStartTime(int t){
	startTime=t;
}

void param_name_obstacleMan::resetMode(InformationProvider *info) {
	setStartTime(180 - info->getRemainingGameTime());
	LHMCountdown=DEFAULT_LHMCountdown;
	hugsLand = false;
}

Vector2f param_name_obstacleMan::getNextPingPoint(Vector2f v,int n){
	return (1.0f*n*MIN_PING_DIST)*v;
}
int param_name_obstacleMan::randDirFixer(){
	srand (time(NULL));
	int random = rand() % 100;
	if(random <= 50) {
		return -1;
	} else {
		return 1;
	}
}
float param_name_obstacleMan::randAngleGen(){
	return OBSTACLEMAN_MAX_ANGLE;
}
Vector2f param_name_obstacleMan::dispChange(InformationProvider *info){
	if(VectorOps::Magnitude(info->getRaftVelocity()) == 0) {
		return Vector2f(0,0);
	}
	Vector2f normalizedVelocityVector=VectorOps::Normalise(info->getRaftVelocity());
	Vector2f referencePoint=(SAFETY_THRESHOLD*1.0f)*normalizedVelocityVector;
	Vector2f leftBoundaryChecked = VectorOps::RotateAnticlockwise(referencePoint, OBSTACLEMAN_DISP_ANGLE) + info->getRaftPosition();
	Vector2f rightBoundaryChecked = VectorOps::RotateAnticlockwise(referencePoint, -OBSTACLEMAN_DISP_ANGLE) + info->getRaftPosition();

	Vector2f leftLandPoint=NULL_POS;
	bool leftLandSpotted = false;
	float rotateAngle=0.0f;
	while(rotateAngle < OBSTACLEMAN_DISP_ANGLE) {
		Vector2f pointToBeChecked = VectorOps::RotateAnticlockwise(referencePoint, rotateAngle) + info->getRaftPosition();
		if(info->requestMapPoint((Vector2i)pointToBeChecked) == 'L' || info->requestMapPoint((Vector2i)pointToBeChecked) == '\0') {
			leftLandPoint = pointToBeChecked;
			leftLandSpotted = true;
			break;
		} else {
			rotateAngle += OBSTACLEMAN_MAX_ANGLE;
		}
	}

	Vector2f rightLandPoint = NULL_POS;
	bool rightLandSpotted = false;
	rotateAngle = 0.0f;
	while(rotateAngle > -OBSTACLEMAN_DISP_ANGLE) {
		Vector2f pointToBeChecked = VectorOps::RotateAnticlockwise(referencePoint, rotateAngle) + info->getRaftPosition();
		if(info->requestMapPoint((Vector2i)pointToBeChecked) == 'L' || info->requestMapPoint((Vector2i)pointToBeChecked) == '\0') {
			rightLandPoint = pointToBeChecked;
			rightLandSpotted = true;
			break;
		} else {
			rotateAngle -= OBSTACLEMAN_MAX_ANGLE;
		}
	}

	if(!leftLandSpotted && !rightLandSpotted) {
		return Vector2f(0, 0);
	} else if(leftLandSpotted && !rightLandSpotted) {
		return leftLandPoint - leftBoundaryChecked;
	} else if(!leftLandSpotted && rightLandSpotted) {
		return rightLandPoint - rightBoundaryChecked;
	} else {
		float leftDisplacement = VectorOps::Magnitude(leftLandPoint - leftBoundaryChecked);
		float rightDisplacement = VectorOps::Magnitude(rightLandPoint - rightBoundaryChecked);
		if(leftDisplacement > rightDisplacement) {
			return leftLandPoint - leftBoundaryChecked;
		} else {
			return rightLandPoint - rightBoundaryChecked;
		}
	}
}
Vector2f param_name_obstacleMan::getObstacleManPosition(Vector2f x,InformationProvider *info){
	/*
	  discard 'x' if time exceeds time threshold
	  if time exceeded return NULL=(-1,-1)
	*/
	if(x == NULL_POS) {
		return info->getRaftPosition();
	}
	if(x == info->getRaftPosition()) {
		resetMode(info);
		return x;
	}

	Vector2f pingPoint;
	int timeSpent=(180 - info->getRemainingGameTime()) - startTime;
	if (timeSpent > OBSTACLEMAN_TIME_THRESHOLD){
		return NULL_POS;
	}

	if(!hugsLand){
		/*
		   Ping in direction of 'x - currentPos' inside buffer region(SAFETY_THRESHOLD)
		   if no land return straight approach vector.
		   else switch on LHM and fix random direction.
		   intialize LHMCountdown

		*/
		//printf("X = %fi + %fj\n", x.x, x.y);
		//printf("Straight Mode | Velocity = %fi + %fj\n", info->getRaftVelocity().x, info->getRaftVelocity().y);
		bool stopPinging=false;
		int tempCounter=1;
		Vector2f normalizedDirectionVector=VectorOps::Normalise(x - info->getRaftPosition());
		while(!stopPinging){
			pingPoint=getNextPingPoint(normalizedDirectionVector,tempCounter);
			tempCounter++;
			if(tempCounter*MIN_PING_DIST>SAFETY_THRESHOLD){
				stopPinging=true;
			}
			else if(info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition()))=='L' || info->requestMapPoint((Vector2i)(pingPoint + info->getRaftPosition())) == '\0'){
				stopPinging=true;
				//printf("Straight Mode | Detected Land or NULL in front\n");
			}
		}
		
		//For straight approach
		if(info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition()))=='W' || info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition()))=='F'){
			//printf("Straight | Moving Straight\n");
			Vector2f displacement= dispChange(info);
			//printf("Straight Mode | Displacement = %fi + %fj\n", displacement.x, displacement.y);
			return (pingPoint+info->getRaftPosition() + displacement);
		}
		//For Non straight approach
		else if (info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition()))=='L'){
			//Switch on land Hug Mode
			//printf("Straight Mode | Switching to Land Hugging Mode\n");
			hugsLand=true;
			direction=randDirFixer();
			Vector2f displacement = dispChange(info);
			lastPointChecked=pingPoint+info->getRaftPosition();
			return lastPointChecked + displacement;
		} else {
			//printf("Straight Mode | Moving Away from Border\n");
			if((pingPoint + info->getRaftPosition()).x >= info->getMapWidth() - RAFT_RADIUS) {
				return Vector2f((pingPoint + info->getRaftPosition()).x - 1.5*RAFT_RADIUS, (pingPoint + info->getRaftPosition()).y);
			} else if((pingPoint + info->getRaftPosition()).x <= RAFT_RADIUS) {
				return Vector2f((pingPoint + info->getRaftPosition()).x + 1.5*RAFT_RADIUS, (pingPoint + info->getRaftPosition()).y);
			} else if((pingPoint + info->getRaftPosition()).y >= info->getMapHeight() - RAFT_RADIUS) {
				return Vector2f((pingPoint + info->getRaftPosition()).x, (pingPoint + info->getRaftPosition()).y - 1.5*RAFT_RADIUS);
			} else if((pingPoint + info->getRaftPosition()).y <= RAFT_RADIUS) {
				return Vector2f((pingPoint + info->getRaftPosition()).x, (pingPoint + info->getRaftPosition()).y + 1.5*RAFT_RADIUS);
			} else {
				return info->getRaftPosition();
			}
			//return (info->getRaftPosition() - 4.0f*pingPoint);
		}
	}

	if(hugsLand){
		/*
		   Ping next point in fixed direction at random angle.
		   
		   Get PosVector

		   If LHMCountdown is zero
		      If current velocity vector is || to target disp vector (within error)
			      switch off LHM
				  reintialize LHMCountdown
				  return 'x'

		  return PosVector
		*/

		//printf("Hugging Land | direction = %d, LHMCount = %d, Velocity = %fi + %fj\n", direction, LHMCountdown, info->getRaftVelocity().x, info->getRaftPosition().y);
		
		float randomAngle=direction*randAngleGen();
		Vector2f normalizedDirectionVector=VectorOps::Normalise(lastPointChecked-info->getRaftPosition());
		Vector2f rotatedVector=VectorOps::RotateAnticlockwise(normalizedDirectionVector,randomAngle);
		bool stopPinging=false;
		int tempCounter=1;
		while(!stopPinging){
			pingPoint=getNextPingPoint(rotatedVector,tempCounter);
			tempCounter++;
			if(tempCounter*MIN_PING_DIST>SAFETY_THRESHOLD){
				stopPinging=true;
			}
			else if(info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition()))=='L' || info->requestMapPoint((Vector2i)(pingPoint + info->getRaftPosition())) == '\0'){
				stopPinging=true;
			}
		}
		
		if(info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition())) != 'L' && info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition())) != '\0'){
			Vector2f normalizedVelocityVector=VectorOps::Normalise(info->getRaftVelocity());
			Vector2f normalizedDispVector=VectorOps::Normalise(x-info->getRaftPosition());
			/*if(VectorOps::Dot(normalizedVelocityVector,normalizedDispVector)>=OBSTACLEMAN_COS_ERROR){
				hugsLand=false;
				Vector2f displacement = dispChange(info);
				return VectorOps::Normalise(x-info->getRaftPosition())+info->getRaftPosition() + displacement;
			} else {*/
				hugsLand=false;
				Vector2f displacement = dispChange(info);
				return pingPoint+info->getRaftPosition() + displacement;
			//}
		} else if(info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition())) == 'L') {
			Vector2f displacement = dispChange(info);
			Vector2f finalVector = VectorOps::Normalise(pingPoint + info->getRaftPosition() - lastPointChecked) + info->getRaftPosition();
			lastPointChecked = pingPoint + info->getRaftPosition();
			//printf("Hug Mode | Current = %fi + %fj, Final = %fi + %fj\n", info->getRaftPosition().x, info->getRaftPosition().y, finalVector.x, finalVector.y);
			return finalVector;
		} else {
			if((pingPoint + info->getRaftPosition()).x >= info->getMapWidth() - RAFT_RADIUS) {
				return Vector2f((pingPoint + info->getRaftPosition()).x - 1.5*RAFT_RADIUS, (pingPoint + info->getRaftPosition()).y);
			} else if((pingPoint + info->getRaftPosition()).x <= RAFT_RADIUS) {
				return Vector2f((pingPoint + info->getRaftPosition()).x + 1.5*RAFT_RADIUS, (pingPoint + info->getRaftPosition()).y);
			} else if((pingPoint + info->getRaftPosition()).y >= info->getMapHeight() - RAFT_RADIUS) {
				return Vector2f((pingPoint + info->getRaftPosition()).x, (pingPoint + info->getRaftPosition()).y - 1.5*RAFT_RADIUS);
			} else if((pingPoint + info->getRaftPosition()).y <= RAFT_RADIUS) {
				return Vector2f((pingPoint + info->getRaftPosition()).x, (pingPoint + info->getRaftPosition()).y + 1.5*RAFT_RADIUS);
			} else {
				return info->getRaftPosition();
			}
		}
		/*
			if(info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition())) != 'L' && LHMCountdown==0){
			hugsLand=false;
			Vector2f displacement = dispChange(info);
			return pingPoint+info->getRaftPosition()+displacement;
		}
		else{
			if(info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition())) != 'L' && LHMCountdown==0){
				Vector2f normalizedVelocityVector=VectorOps::Normalise(info->getRaftVelocity());
				Vector2f normalizedDispVector=VectorOps::Normalise(x-info->getRaftPosition());
				if(VectorOps::Dot(normalizedVelocityVector,normalizedDispVector)>=OBSTACLEMAN_COS_ERROR){
					hugsLand=false;
					LHMCountdown=DEFAULT_LHMCountdown;
					Vector2f displacement = dispChange(info);
					return (SAFETY_THRESHOLD*1.0f)*VectorOps::Normalise(x-info->getRaftPosition())+info->getRaftPosition() + displacement;
				}
			} else {
				Vector2f displacement = dispChange(info);
				Vector2f finalVector = (SAFETY_THRESHOLD*1.0f) * VectorOps::Normalise(pingPoint + info->getRaftPosition() - lastPointChecked) + info->getRaftPosition();
				lastPointChecked = pingPoint + info->getRaftPosition() + displacement;
				//printf("Hug Mode | Current = %fi + %fj, Final = %fi + %fj\n", info->getRaftPosition().x, info->getRaftPosition().y, finalVector.x, finalVector.y);
				return finalVector;
			}
		}
		*/
			/*{
			if(info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition())) != 'L' && LHMCountdown==0){
				Vector2f normalizedVelocityVector=VectorOps::Normalise(info->getRaftVelocity());
				Vector2f normalizedDispVector=VectorOps::Normalise(x-info->getRaftPosition());
				if(VectorOps::Dot(normalizedVelocityVector,normalizedDispVector)>=OBSTACLEMAN_COS_ERROR){
					hugsLand=false;
					LHMCountdown=DEFAULT_LHMCountdown;
					Vector2f displacement = dispChange(info);
					return (SAFETY_THRESHOLD*1.0f)*VectorOps::Normalise(x-info->getRaftPosition())+info->getRaftPosition() + displacement;
				}
			} else {
				Vector2f displacement = dispChange(info);
				Vector2f finalVector = (SAFETY_THRESHOLD*1.0f) * VectorOps::Normalise(pingPoint + info->getRaftPosition() - lastPointChecked) + info->getRaftPosition();
				lastPointChecked = pingPoint + info->getRaftPosition() + displacement;
				//printf("Hug Mode | Current = %fi + %fj, Final = %fi + %fj\n", info->getRaftPosition().x, info->getRaftPosition().y, finalVector.x, finalVector.y);
				return finalVector;
			}
		}*/
	}
}
/*
Vector2f obstacleMan::dispChange(InformationProvider *info){
	Vector2f normalizedVelocityVector=VectorOps::Normalise(info->getRaftVelocity());
	Vector2f referencePoint=(SAFETY_THRESHOLD*1.0f)*normalizedVelocityVector;
	Vector2f leftBoundaryChecked = VectorOps::RotateAnticlockwise(referencePoint, OBSTACLEMAN_DISP_ANGLE) + info->getRaftPosition();
	Vector2f rightBoundaryChecked = VectorOps::RotateAnticlockwise(referencePoint, -OBSTACLEMAN_DISP_ANGLE) + info->getRaftPosition();

	Vector2f leftLandPoint=NULL_POS;
	bool leftLandSpotted = false;
	float rotateAngle=0.0f;
	while(rotateAngle < OBSTACLEMAN_DISP_ANGLE) {
		Vector2f pointToBeChecked = VectorOps::RotateAnticlockwise(referencePoint, rotateAngle) + info->getRaftPosition();
		if(info->requestMapPoint((Vector2i)pointToBeChecked) == 'L') {
			leftLandPoint = pointToBeChecked;
			leftLandSpotted = true;
			break;
		} else {
			rotateAngle += OBSTACLEMAN_MAX_ANGLE;
		}
	}

	Vector2f rightLandPoint = NULL_POS;
	bool rightLandSpotted = false;
	rotateAngle = 0.0f;
	while(rotateAngle > -OBSTACLEMAN_DISP_ANGLE) {
		Vector2f pointToBeChecked = VectorOps::RotateAnticlockwise(referencePoint, rotateAngle) + info->getRaftPosition();
		if(info->requestMapPoint((Vector2i)pointToBeChecked) == 'L') {
			rightLandPoint = pointToBeChecked;
			rightLandSpotted = true;
			break;
		} else {
			rotateAngle -= OBSTACLEMAN_MAX_ANGLE;
		}
	}

	if(!leftLandSpotted && !rightLandSpotted) {
		return Vector2f(0, 0);
	} else if(leftLandSpotted && !rightLandSpotted) {
		return leftLandPoint - leftBoundaryChecked;
	} else if(!leftLandSpotted && rightLandSpotted) {
		return rightLandPoint - rightBoundaryChecked;
	} else {
		int leftDisplacement = VectorOps::Magnitude(leftLandPoint - leftBoundaryChecked);
		int rightDisplacement = VectorOps::Magnitude(rightLandPoint - rightBoundaryChecked);
		if(leftDisplacement > rightDisplacement) {
			return leftLandPoint - leftBoundaryChecked;
		} else {
			return rightLandPoint - rightBoundaryChecked;
		}
	}
}
Vector2f obstacleMan::getObstacleManPosition(Vector2f x,InformationProvider *info){
	/*
	  discard 'x' if time exceeds time threshold
	  if time exceeded return NULL=(-1,-1)
	*//*
	if(x == info->getRaftPosition()) {
		return x;
	}

	Vector2f pingPoint;
	int timeSpent=(180 - info->getRemainingGameTime()) - startTime;
	if (timeSpent > OBSTACLEMAN_TIME_THRESHOLD){
		return NULL_POS;
	}

	if(!hugsLand){*/
		/*
		   Ping in direction of 'x - currentPos' inside buffer region(SAFETY_THRESHOLD)
		   if no land return straight approach vector.
		   else switch on LHM and fix random direction.
		   intialize LHMCountdown

		*//*
		printf("Straight Mode | Velocity = %fi + %fj\n", info->getRaftVelocity().x, info->getRaftPosition().y);
		bool stopPinging=false;
		int tempCounter=1;
		Vector2f normalizedDirectionVector=VectorOps::Normalise(x - info->getRaftPosition());
		while(!stopPinging){
			pingPoint=getNextPingPoint(normalizedDirectionVector,tempCounter);
			tempCounter++;
			if(tempCounter*MIN_PING_DIST>SAFETY_THRESHOLD){
				stopPinging=true;
			}
			else if(info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition()))=='L'){
				stopPinging=true;
				break;
				printf("Straight Mode | Detected Land in front\n");
			}
		}
		
		//For straight approach
		if(info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition()))=='W' || info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition()))=='F'){
			printf("Straight | Moving Straight\n");
			Vector2f displacement= dispChange(info);
			printf("Straight Mode | Displacement = %fi + %fj\n", displacement.x, displacement.y);
			return (pingPoint+info->getRaftPosition() + displacement);
		}
		//For Non straight approach
		else if (info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition()))=='L'){
			//Switch on land Hug Mode
			printf("Straight Mode | Switching to Land Hugging Mode\n");
			hugsLand=true;
			direction=randDirFixer();
			//direction=-1;
			LHMCountdown=DEFAULT_LHMCountdown;
			lastPointChecked=pingPoint+info->getRaftPosition();
		} else {
			printf("Straight Mode | Moving Away from Border\n");
			return (info->getRaftPosition() - pingPoint);
		}
	}

	if(hugsLand){*/
		/*
		   Ping next point in fixed direction at random angle.
		   
		   Get PosVector

		   If LHMCountdown is zero
		      If current velocity vector is || to target disp vector (within error)
			      switch off LHM
				  reintialize LHMCountdown
				  return 'x'

		  return PosVector
		*/
/*
		printf("Hugging Land | direction = %d, LHMCount = %d, Velocity = %fi + %fj\n", direction, LHMCountdown, info->getRaftVelocity().x, info->getRaftPosition().y);
		
		float randomAngle=direction*randAngleGen();
		Vector2f normalizedDirectionVector=VectorOps::Normalise(lastPointChecked-info->getRaftPosition());
		Vector2f rotatedVector=VectorOps::RotateAnticlockwise(normalizedDirectionVector,randomAngle);
		bool stopPinging=false;
		int tempCounter=1;
		while(!stopPinging){
			pingPoint=getNextPingPoint(rotatedVector,tempCounter);
			tempCounter++;
			if(tempCounter*MIN_PING_DIST>SAFETY_THRESHOLD){
				stopPinging=true;
			}
			else if(info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition()))=='L'){
				stopPinging=true;
				break;
			}
		}

		if(LHMCountdown >  0)
				LHMCountdown--;
			
		
		if(info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition())) != 'L' && LHMCountdown==0){
			hugsLand=false;
			Vector2f displacement = dispChange(info);
			return pingPoint+info->getRaftPosition()+displacement;
		}
		else{
			if(info->requestMapPoint((Vector2i)(pingPoint+info->getRaftPosition())) != 'L' && LHMCountdown==0){
				Vector2f normalizedVelocityVector=VectorOps::Normalise(info->getRaftVelocity());
				Vector2f normalizedDispVector=VectorOps::Normalise(x-info->getRaftPosition());
				if(VectorOps::Dot(normalizedVelocityVector,normalizedDispVector)>=OBSTACLEMAN_COS_ERROR){
					hugsLand=false;
					LHMCountdown=DEFAULT_LHMCountdown;
					Vector2f displacement = dispChange(info);
					return (SAFETY_THRESHOLD*1.0f)*VectorOps::Normalise(x-info->getRaftPosition())+info->getRaftPosition() + displacement;
				}
			} else {
				Vector2f displacement = dispChange(info);
				Vector2f finalVector = (SAFETY_THRESHOLD*1.0f) * VectorOps::Normalise(pingPoint + info->getRaftPosition() - lastPointChecked) + info->getRaftPosition();
				lastPointChecked = pingPoint + info->getRaftPosition() + displacement;
				printf("Hug Mode | Current = %fi + %fj, Final = %fi + %fj\n", info->getRaftPosition().x, info->getRaftPosition().y, finalVector.x, finalVector.y);
				return finalVector;
			}
		}
	}
}
*/
Vector2f param_name_cannon::opponentVelocityVector(Vector2f opponentInitialPosition, InformationProvider *info)
{
	Vector2f opponentFinalPosition = info->getOpponentRaftPosition();
	Vector2f opponentVelocity = (opponentFinalPosition - opponentInitialPosition) * 1.0f;
	return opponentVelocity;
}
Vector2f param_name_cannon::cannonVector(InformationProvider *info )
{
	//int random,mul;
	float mul;
	/*if(RAFT_DRAG_REGULAR<20) mul=15.0f;
	else mul=10.0f;*/
	mul=7.5f;
	//mul=(130-RAFT_DRAG_REGULAR)/8.0f;
	if(seenOnce==false)
	{
		int sector;
		entered=false;
		Vector2f cannonDir, currentR = info->getRaftPosition();
		if (currentR.x<1366/2&&currentR.y<768/2) sector=0;
		else if(currentR.x>1366/2&&currentR.y<768/2) sector=-1;
		else if(currentR.x<1366/2&&currentR.y>768/2) sector=1;
		else sector = 2;
		int iSecret;
	srand (time(NULL));
	iSecret = (rand()+timeCheck-rand()) % 100 + 1;
	float rotateAngle=(float)iSecret/100.0f*PI/4;
	cannonDir=Vector2f(683,384);
	cannonDir=VectorOps::RotateAnticlockwise(cannonDir,rotateAngle+sector*PI/2);
	timeCheck++;
	onTime=false;
	cannonDirection=cannonDir;
	lastSeenPosition=info->getOpponentRaftPosition();

	}
		
	if((info->getOpponentRaftPosition()==Vector2f (-1,-1))&&seenOnce==true)
	{
		if(timeCheck>5*GAME_DESIRED_UPDATE_FPS) seenOnce=false;
		timeCheck++; onTime=false;
		cannonDirection = (lastSeenPosition + prevVelocity*(float)mul) - info->getRaftPosition();
		entered=false;
		int iSecret;
		srand (time(NULL));
		iSecret = (rand()+timeCheck-rand()) % 100 + 1;
		float rotateAngle=(float)iSecret/100.0f*PI/8;
		cannonDirection=VectorOps::RotateAnticlockwise(cannonDirection,rotateAngle);
	}

	else if(info->getOpponentRaftPosition()!=Vector2f (-1,-1))
	{
		seenOnce=true;
		//int timeDelay = (int)(CANNONBALL_FIRE_MIN_LAG*GAME_DESIRED_UPDATE_FPS);
		if(entered==false||onTime==false) 
		{
			if(timeCheck%timeDelay==0) { timeCheck=1; onTime=true; }
			else 
			{
				timeCheck++;
				cannonDirection=Vector2f(0,0);
				onTime=false;
				goto lb;
			}
		}
		entered=true;
		Vector2f opponentInitialPosition = info->getOpponentRaftPosition();
		Vector2f currentPosition = info->getRaftPosition();
		if(timeCheck%timeDelay==0)
		//if((timeCheck)%30==0)
		{
		//Vector2f velocity = cannon::opponentVelocityVector(prevPosition,info);
		if(timeCheck>GAME_DESIRED_UPDATE_FPS) timeCheck=1;
		//	timeCheck=0;
			prevPosition = info->getOpponentRaftPosition();
		//prevVelocity = velocity;
		}
		//Vector2f velocity;
		prevVelocity = param_name_cannon::opponentVelocityVector(prevPosition,info);
		//prevVelocity = velocity;
	//	cannonDirection = (opponentInitialPosition + prevVelocity*mul) - currentPosition;
	cannonDirection = (opponentInitialPosition ) - currentPosition;
//	if(timeCheck>=timeDelay) cannonDirection = opponentInitialPosition - currentPosition;
	timeCheck++;
	lastSeenPosition=info->getOpponentRaftPosition();
	}
	lb: ;
	if(onTime==false) entered=false;
	return cannonDirection;
}
Vector2f param_name::flee(InformationProvider *info){
	Vector2f enemyLocation=info->getOpponentRaftPosition();
	Vector2f enemyDispLocation=enemyLocation-info->getRaftPosition();
	Vector2f normalizedEnemyDispLocation=VectorOps::Normalise(enemyDispLocation);
	Vector2f rotatedNormalizedEnemyDispLocation=VectorOps::RotateAnticlockwise(normalizedEnemyDispLocation,3.0f*PI/4);
	Vector2f rFinal=obstacle.getObstacleManPosition((RAFT_VISIBILITY_RADIUS*1.0f)*rotatedNormalizedEnemyDispLocation+info->getRaftPosition(),info);
	if(rFinal==NULL_POS){
		obstacle.resetMode(info);
		rotatedNormalizedEnemyDispLocation=VectorOps::RotateAnticlockwise(rotatedNormalizedEnemyDispLocation,PI);
		rFinal=obstacle.getObstacleManPosition(rotatedNormalizedEnemyDispLocation+info->getRaftPosition(),info);
	}
	return rFinal;
}
Vector2f param_name::hide(InformationProvider *info) {
	return info->getRaftPosition();
}

Vector2f param_name::enemyPursuit(InformationProvider *info) {
	Vector2f enemyPositionCenter = info->getOpponentRaftPosition();
	Vector2f pointOnCircle=enemyPositionCenter + (ENEMY_PURSUIT_RADIUS*1.0f)*VectorOps::RotateAnticlockwise((VectorOps::Normalise(info->getRaftPosition()-enemyPositionCenter)),PI/3.0f);
	if(enemyPositionCenter == Vector2f(-1,-1)) {
		return NULL_POS;
	} else {
		Vector2f finalPos = obstacle.getObstacleManPosition(pointOnCircle, info);
		if(finalPos == NULL_POS) {
			obstacle.resetMode(info);
		}
		return obstacle.getObstacleManPosition(pointOnCircle, info);
	}
}

void param_name::updateDatabase(InformationProvider *info) {

	// Fish Module Update DB
	//printf("updateDatabase\n");
	//Remove from black list
	for(int i=0;i<NUMBER_OF_FISHES;i++){
		if(fish[i].blackListed==true&&((180-info->getRemainingGameTime())-fish[i].blackListTime)>FISHLOCATION_MAX_BLACKLIST_TIME){
			fish[i].blackListed=false;
			fish[i].blackListTime=0;
		}
	}
	bool fishPresentInDatabase=false;
	Vector2i vissibleFishLocation[NUMBER_OF_FISHES];
	int numberOfFish=info->getAllVisibleFishPositions(vissibleFishLocation);
	//Insert Data
	for(int i=0;i<numberOfFish;i++){
		fishPresentInDatabase=false;
		for(int j=0;j<NUMBER_OF_FISHES;j++){
			if(vissibleFishLocation[i]==fish[j].location){
				fishPresentInDatabase=true;
				break;
			}	
		}
		if(!fishPresentInDatabase){
			for(int j=0;j<NUMBER_OF_FISHES;j++){
				if(fish[j].location==Vector2i(0,0)){
					fish[j].location=vissibleFishLocation[i];
					fish[j].caught=false;
					break;
				}
			}
		}
	}/*
	for(int i=0;i<NUMBER_OF_FISHES;i++){
		printf("%di + %dj %d\n",fish[i].location.x,fish[i].location.y,fish[i].caught);
	}*/
	//Remove Caught fishes

		for(int j=0;j<NUMBER_OF_FISHES;j++){
			if( fish[j].location!=Vector2i(0,0)&&(info->requestMapPoint(fish[j].location)=='W'||info->requestMapPoint(fish[j].location)=='L') ){
				fish[j].caught=true;
			}
		}

	// Update Sector Matrix
}

Vector2f param_name::catchFish(InformationProvider *info){
	//printf("CatchFish\n");
	int indexOfClosestFirst=0;
	int indexOfSecondClosestFish;
	Vector2i locationOfClosestFish=Vector2i(0,0);
	float minMagnitude=1000000;
	if(fish[0].location!=Vector2i(0,0)){
	  for(int i=0;i<NUMBER_OF_FISHES;i++){
		  if(!fish[i].blackListed && fish[i].caught==false && minMagnitude>VectorOps::Magnitude((Vector2f)fish[i].location-info->getRaftPosition())&&fish[i].location!=Vector2i(0,0)){
			  indexOfSecondClosestFish=indexOfClosestFirst;
			  indexOfClosestFirst=i;
			  locationOfClosestFish=fish[i].location;
			  minMagnitude=VectorOps::Magnitude((Vector2f)fish[i].location-info->getRaftPosition());
		  }
	   }
    }
	Vector2f rFinal=obstacle.getObstacleManPosition((Vector2f)locationOfClosestFish,info);
	if(rFinal==NULL_POS){
		obstacle.resetMode(info);
		fish[indexOfClosestFirst].blackListed=true;
		fish[indexOfClosestFirst].blackListTime=180-info->getRemainingGameTime();
		rFinal=obstacle.getObstacleManPosition((Vector2f)fish[indexOfSecondClosestFish].location,info);
	}
	//printf("**********************%d %d MinFishLoc %fi + %fj  %d  %d\n",locationOfClosestFish.x, locationOfClosestFish.y, rFinal.x,rFinal.y, indexOfClosestFirst, indexOfSecondClosestFish);
	return rFinal;
}

int param_name::decisionMaker(InformationProvider *info) {
	
	// Always Fire Cannon
	int decision = 1;

	// Survival Critical => STOP ASSHOLE
	/*
	Flee
	If Health is less than 20 and enemy is in vissibility location
	     call flee ;
    Else
	     Hide ;
	*/
/*	if(info->getRaftHealth() <= 15){
		return decision | (1 << 2);
	}*/
	if(info->getRaftHealth()<=40 && info->getOpponentRaftPosition()!=Vector2f (-1,-1)){
		     return decision | (1<<5) ;
	}


	if(info->getRaftHealth() > 20 && info->getRaftHealth() < 30) {
		if(info->getOpponentRaftPosition() != Vector2f(-1,-1)) {
			return decision | (1 << 5);
		} else {
			return decision | (1 << 2);
		}
	}
	
	/* If Fish Win Guarantee
			If enemyFound
				if H > 0.6
					Pursue
				else
					FLEE or STOP ASSHOLE
			else
				STOP ASSHOLE
	*/
	
	if(info->getNumberOfCapturedFish() > NUMBER_OF_FISHES / 2) {
		Vector2f enemyPosition = info->getOpponentRaftPosition();
		if(enemyPosition != Vector2f(-1,-1)) {
			if(info->getRaftHealth() > 60) {
				return decision | (1 << 1);
			} else {
				return decision | (1 << 5);
			}
		} else {
			return decision | (1 << 2);
		}
	}
	
	/* If 0.2 < H <= 0.4 and Fish = Less than Half
			If enemyFound
				FLEE (if possible) or STOP ASSHOLE
			else if CAN FISH
				FISH FISH FISH!
			else
				STOP ASSHOLE
	*/
	
	if(info->getRaftHealth() >= 30 && info->getRaftHealth() <= 40) {
		Vector2f enemyPosition = info->getOpponentRaftPosition();
		if(enemyPosition != Vector2f(-1,-1)) {
			return decision | (1 << 5);
		} else if(canFish()) {
			return decision | (1 << 3);
		} else {
			return decision | (1 << 4);
		}
	}
	
	/* If 0.4 < H <= 0.6 and Fish = LESS THAN HALF
			if enemyFound
				FLEE (If Possible) or STOP ASSHOLE
			else if CAN FISH
				FISH
			else EXPLORE
	*/
	
	if(info->getRaftHealth() > 40 && info->getRaftHealth() <= 60) {
		Vector2f enemyPosition = info->getOpponentRaftPosition();
		if(enemyPosition != Vector2f(-1,-1)) {
			return decision | (1 << 5);
		}
		else if(canFish()){
			return decision | (1 << 3);
		}
		else{
			return decision | (1 << 4);
		}
	}
	

	/* H > 0.6 and Fish = LESS THAN HALF
			if enemyFound
				Maaro BC!
			else if CAN FISH
				MACHCHI KA PAKDO
			else
				awara gardi karo
	*/
	
	if(info->getRaftHealth() > 60) {
		Vector2f enemyPosition = info->getOpponentRaftPosition();
		if(enemyPosition != Vector2f(-1,-1)) {
			return decision | (1 << 1);
		}
		else if(canFish()){
			return decision | (1 << 3);
		}
		else{
			return decision | (1 << 4);
		}
	}
	
}

void param_name::initialise(InformationProvider* info)
{
	obstacle.resetMode(info);
	for(int i=0;i<NUMBER_OF_FISHES;i++){
		fish[i].location=Vector2i(0,0);
		fish[i].caught=false;
		fish[i].blackListed=false;
		fish[i].blackListTime=0;
	}
	explore.chooseQueueOrder(info);
	// Initialize Sector Matrix
}

bool param_name::canFish(){
	for(int i=0;i<NUMBER_OF_FISHES;i++){
		if(!fish[i].blackListed && !fish[i].caught && fish[i].location != Vector2i(0,0)){
			return true;
		}
	}
	return false;
}

RaftControls param_name::controlRaft(InformationProvider* info)
{
	Vector2f rFinal = Vector2f(0,0);
	Vector2f cannonV = Vector2f(0,0);
	bool needWarpSpeed = false;
	/* Main function
	DO NOT CHANGE ANYTHING OR BAD THINGS WILL HAPPEN!
	YOU HAVE BEEN WARNED!*/
	updateDatabase(info);
	int decisionIndex=decisionMaker(info);
	//printf("decision = %d\n", decisionIndex);
	// Print BOT Status
	Vector2i fishes[21];
	printf("BOT Status | HP = %d, Velc = %.3gi + %.3gj, Pos = %.3gi + %.3gj, EnemPos = %.3gi + %.3gj, Fishes = %d\n", info->getRaftHealth(), info->getRaftVelocity().x, info->getRaftVelocity().y, info->getRaftPosition().x, info->getRaftPosition().y, info->getOpponentRaftPosition().x, info->getOpponentRaftPosition().y, info->getAllVisibleFishPositions(fishes));

	printf("Decision: %d => ", decisionIndex);
	if((decisionIndex >> 0) & 1 == 1){
		printf("Fire Cannon, ");
		cannonV += cannonFire.cannonVector(info);
	}
	if((decisionIndex >> 1) & 1 == 1){
	printf("Pursue Enemy\n");
		needWarpSpeed = true;
	    rFinal += enemyPursuit(info);
	}
	if((decisionIndex >> 2) & 1 == 1){
	printf("Hide/Stop\n");
		rFinal += hide(info);
	}
	if((decisionIndex >> 3) & 1 == 1){
		printf("Go Fish\n");
		rFinal += catchFish(info);
	}
	if((decisionIndex >> 4) & 1 == 1){
		printf("Explore\n");
		Vector2f beforeFinal=explore.explorePoint(info);
		Vector2f temp = beforeFinal;
		beforeFinal = obstacle.getObstacleManPosition(beforeFinal, info);
		if(beforeFinal==NULL_POS){
			obstacle.resetMode(info);
			explore.blacklistExplore(info, temp);
			beforeFinal = obstacle.getObstacleManPosition(explore.explorePoint(info), info);
		}
		rFinal+=beforeFinal;
	}
	if((decisionIndex >> 5) & 1==1){
		printf("Flee\n");
		needWarpSpeed = true;
		rFinal+=flee(info);
	}
	if(rFinal.x <= 0 && rFinal.y <= 0) {
		rFinal = info->getRaftPosition();
	}
	//rFinal += catchFish(info);
	
	motorFunction(rFinal,info, needWarpSpeed);
	printf("Velc = %f | Thrust = %fi + %fj, Brake = %d\n\n", VectorOps::Magnitude(info->getRaftVelocity()), movementControls.thrustVector.x, movementControls.thrustVector.y, movementControls.brakeApplied);
	/*
	Vector2i fishLocs[22];
	int a = info->getAllVisibleFishPositions(fishLocs);
	Vector2f X = (Vector2f)fishLocs[0];
	if(a == 0) {
		X = Vector2f(1300, 300);
	} else {
		obstacle.resetMode(info);
	}
	//Vector2f X = Vector2f(927, 402);
	Vector2f x = (RAFT_VISIBILITY_RADIUS*1.0f * VectorOps::Normalise(X - info->getRaftPosition())) + info->getRaftPosition();
	//Your AI code goes here
	Vector2f finalVector=obstacle.getObstacleManPosition(x,info);
	if(finalVector == NULL_POS) {
		obstacle.resetMode(info);
		finalVector=obstacle.getObstacleManPosition(Vector2f(1300, 300),info);
	}

	cannonV = cannonFire.cannonVector(info);
	motorFunction(finalVector = (enemyPursuit(info) != Vector2f(-1,-1)) ? enemyPursuit(info) : info->getRaftPosition(), info);
	*/
	return RaftControls(movementControls.thrustVector, movementControls.brakeApplied, cannonV);
}

void param_name::getTeamName(char teamName[])
{
	strcpy_s(teamName, 256, "Param-Name");
}