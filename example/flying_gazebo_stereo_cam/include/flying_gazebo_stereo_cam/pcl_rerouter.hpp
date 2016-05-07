/* Copyright (c) 2016, Stefan Isler, islerstefan@bluewin.ch
 * 
 * This file is part of ros_tools, a set of utilities when working with the Robotic Operating System.
 * 
 * It is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
It is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public License
along with it. If not, see <http://www.gnu.org/licenses/>.
*/

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

namespace ros_tools
{
  /*! Class that listens on a pcl topic and reroutes what it receives to another pcl topic or to a service.
   * Current implementation forwards single packages on demand.
   * 
   * Listens to "in", publishes to "out"
   */
  class PclRerouter
  {
  public:
    PclRerouter( ros::NodeHandle nh );
    
    /*! Reroutes the next incoming pointcloud to the output.
     * @param max_wait_time Max wait time before rerouting is considered to have failed.
     * @return True if a data packet was rerouted.
     */
    bool rerouteOneToTopic(ros::Duration max_wait_time = ros::Duration(0.01));
    
    
    /*! Reroutes the next incoming pointcloud to the service.
     * @param max_wait_time Max wait time before rerouting is considered to have failed.
     * @return True if a data packet was rerouted.
     */
    bool rerouteOneToSrv();
    
  protected:
    /*! Called for incoming pointclouds.
     */
    void pclCallback( const sensor_msgs::PointCloud2ConstPtr& msg );
    
  protected:
    ros::NodeHandle nh_;
    ros::Subscriber pcl_subscriber_;
    ros::Publisher pcl_publisher_;
    ros::ServiceClient pcl_service_caller_;
    
    bool forward_one_;
    bool has_published_one_;
    
    bool one_to_srv_;
    bool service_response_;
  };
  
}