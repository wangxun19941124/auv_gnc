#ifndef LONG_TRAJECTORY
#define LONG_TRAJECTORY

#include "auv_core/auv_core_headers.hpp"
#include "auv_guidance/abstract_trajectory.hpp"
#include "auv_guidance/simultaneous_trajectory.hpp"
#include "auv_guidance/min_jerk_time_solver.hpp"
#include "auv_guidance/min_jerk_trajectory.hpp"
#include "auv_guidance/tgen_limits.hpp"
#include "auv_guidance/waypoint.hpp"

#include "math.h"
#include <vector>

namespace auv_guidance
{
// Defines a trajectory occuring over a long distance. Contains three travel phases: speed up, cruise, and slow down
// Speed up and slow down are both mirrored S-curves about the cruise region (assumes vehicle starts and ends at rest)
class LongTrajectory : public Trajectory
{
private:
   SimultaneousTrajectory *stPreRotation_, *stSpeedUp_, *stCruise_, *stSlowDown_, *stPostRotation_;
   auv_core::auvConstraints *auvConstraints_;
   std::vector<SimultaneousTrajectory *> stList_;
   std::vector<double> stTimes_;
   Waypoint *wStart_, *wEnd_, *wPreTranslate_, *wCruiseStart_, *wCruiseEnd_, *wPostTranslate_;
   Eigen::Quaterniond qStart_, qEnd_, qCruise_;

   Eigen::Vector3d unitVec_, deltaVec_, cruiseStartPos_, cruiseEndPos_, cruiseVel_;
   double totalDuration_, rotationDuration1_, rotationDuration2_, accelDuration_, cruiseDuration_;
   double cruiseRatio_, cruiseSpeed_;
   bool newTravelHeading_;

public:
   EIGEN_MAKE_ALIGNED_OPERATOR_NEW

   LongTrajectory(Waypoint *start, Waypoint *end, auv_core::auvConstraints *constraints, double cruiseRatio, double cruiseSpeed);
   void initTrajectory();
   void initWaypoints();
   void initSimultaneousTrajectories();
   double computeRotationDuration(Eigen::Quaterniond qRel);
   double getDuration();
   auv_core::Vector13d computeState(double time);
   auv_core::Vector6d computeAccel(double time);
};
} // namespace auv_guidance

#endif