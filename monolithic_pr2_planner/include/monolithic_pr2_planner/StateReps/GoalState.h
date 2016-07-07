#pragma once
#include <monolithic_pr2_planner/StateReps/GraphState.h>
#include <monolithic_pr2_planner/StateReps/RobotState.h>
#include <monolithic_pr2_planner/StateReps/ContObjectState.h>
#include <vector>

namespace monolithic_pr2_planner {
    // TODO: generalize this state . also have free angle defaults?
    // TODO: implement setgoal
    class GoalState {
        public:
            GoalState(){ };
            GoalState(RobotState goal_state, double xyz_tol, 
                     double roll_tol, double pitch_tol, double yaw_tol);
            bool isSatisfiedBy(const GraphStatePtr& graph_state);
            void storeAsSolnState(const GraphStatePtr& state){ m_full_goal_state = state; };
            GraphStatePtr getSolnState(){ return m_full_goal_state; };
            bool isSolnStateID(int state_id);
            void addPotentialSolnState(const GraphStatePtr& graph_state);
            DiscObjectState getObjectState() const { return m_goal_state.getObjectStateRelMap().getDiscObjectState(); };
            DiscObjectState getObjectStateRelBody() const { return m_goal_state.getObjectStateRelBody(); };
            RobotState getRobotState() const { return m_goal_state; };
            void setGoal(RobotState goal_state){m_goal_state = goal_state;};
            bool withinXYZTol(const GraphStatePtr& graph_state);
            void visualize();
            bool isStateNearDesiredBase(const GraphStatePtr& graph_state);
        private:
            vector<int> m_possible_goals;
            RobotState m_goal_state;
            GraphStatePtr m_full_goal_state;
            std::vector<double> m_tolerances;
            double l_free_angle;
            double r_free_angle;
    };
    typedef boost::shared_ptr<GoalState> GoalStatePtr;
}
