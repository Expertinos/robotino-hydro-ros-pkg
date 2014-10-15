
/*
 * RobotinoMotionClient.cpp
 *
 *  Created on: 2011
 *      Author: indorewala@servicerobotics.eu
 *	Modified on: 2014
 *		Author: expertinos.unifei@gmail.com
 */

#include "RobotinoMotionClient.h"
#include <queue>
#include <iostream>
#include "findpath.cpp"


RobotinoMotionClient::RobotinoMotionClient():
	client_( "motion", false),
	max_time_( 1.0 )
{
	goal_sub_ = nh_.subscribe( "goal", 1,
			&RobotinoMotionClient::goalCallback, this );
}

RobotinoMotionClient::~RobotinoMotionClient()
{
	goal_sub_.shutdown();
}

void RobotinoMotionClient::goalCallback( const robotino_motion::MotionGoalConstPtr& msg )
{
	robotino_motion::MotionGoal goal;

/*	goal.move_x = msg->move_x;
	goal.move_y = msg->move_y;
	goal.move_phi = msg->move_phi;
	goal.movement_type = msg->movement_type;
	goal.task_type = msg->task_type;
	goal.interruption_condition = msg->interruption_condition;
	goal.alignment_device = msg->alignment_device;

	ROS_INFO( "Pushing goal (move_x[m], move_y[m], move_phi[rad], "
			"movement_type, task_type, interruption_condition, alignment_device) = "
			"(%f, %f, %f, %d, %d, %d, %d)",
			goal.move_x, goal.move_y, goal.move_phi, goal.movement_type, goal.task_type,
			goal.interruption_condition, goal.alignment_device);
*/
	astar();

	goal.move_phi = 0;
	goal.movement_type = 0;
	goal.task_type = 0;
	goal.interruption_condition = 0;
	goal.alignment_device = 0;

	if(!queue.empty())
	{

		goal.move_x = queue.front();
		queue.pop();
		goal.move_y = queue.front();
		queue.pop();
		queue_.push(goal);
		ROS_INFO("%d", queue_.size());
	}else
	{
		if(checkServer())
		{
			popGoalCallback(queue_);
		}
	}

}

void RobotinoMotionClient::popGoalCallback( const std::queue<robotino_motion::MotionGoal> )
{
	robotino_motion::MotionGoal goal;

		if(!queue_.empty())
		{
			goal = queue_.front();
			queue_.pop();
			std::cout << goal;
			ROS_INFO("%d", queue_.size());
			sendGoal(goal);

		}

}

void RobotinoMotionClient::doneCallBack( const actionlib::SimpleClientGoalState& state,
			const robotino_motion::MotionResultConstPtr& result)
{
	ROS_INFO("Finished in state [%s]", state.toString().c_str());
	ROS_INFO("Answer: %i", result->achieved_goal);
	popGoalCallback(queue_);
}

bool RobotinoMotionClient::checkServer()
{
	for( int i = 0; i < 5; ++i)
	{
		ros::spinOnce();
		if( client_.waitForServer( ros::Duration( 1.0 ) ) )
		{
			ROS_INFO( "Connected to the motion server" );
			return true;
		}
		else
		{
			ROS_INFO( "Waiting for motion server" );
		}
	}

	ROS_ERROR( "motion server not running" );
	return false;
}

void RobotinoMotionClient::spin()
{
	ros::Rate loop_rate ( 5 );
	ros::Time start_time = ros::Time::now();

	while( nh_.ok() )
	{
		if( client_.waitForResult( ros::Duration( 1.0 ) ) )
		{
			ROS_INFO("Motion succeeded");
			break;
		}
		else
		{
			ROS_INFO("Motion is being executed");
		}

		if( ( ros::Time::now() - start_time ).toSec() > max_time_ )
		{
			ROS_INFO( "Timeout: Aborting Motion" );
			client_.cancelAllGoals();
			break;
		}

		ros::spinOnce();
		loop_rate.sleep();
	}
}

void RobotinoMotionClient::setMaxTime( const float& time )
{
	max_time_ = time;
}

void RobotinoMotionClient::sendGoal( const robotino_motion::MotionGoal& goal )
{
	client_.sendGoal( goal , boost::bind(&RobotinoMotionClient::doneCallBack, this, _1, _2), Client::SimpleActiveCallback(), Client::SimpleFeedbackCallback());

	ROS_INFO("Goal sent");

}
