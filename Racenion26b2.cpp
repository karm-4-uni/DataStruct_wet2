// You can edit anything you want in this file.
// However, you need to implement all public Racenion functions, which are provided below as a template.

#include "Racenion26b2.h"

Racenion::Racenion() {}

Racenion::~Racenion() {}

StatusType Racenion::add_team(int teamId) {

	if(teamId <= 0) {
		return  StatusType::INVALID_INPUT;
	}
	if (teamsById.search(teamId)) {
	return StatusType::FAILURE;
	}
	try {
		auto newteam = std::make_shared<Team>(teamId);
		teamsById.insert( newteam  ,teamId);
		MotivationKey secondKey = MotivationKey(teamId);
		teamsByMotivation.insert(newteam,secondKey);

return  StatusType::SUCCESS;
	} catch (const std::bad_alloc&) {
		return  StatusType::ALLOCATION_ERROR;
	}

}

StatusType Racenion::remove_team(int teamId) {
	if(teamId <= 0 ) {
		return  StatusType::INVALID_INPUT;
	}
	if(!teamsById.search(teamId)) {
		return StatusType::FAILURE; // team dosnt exist
	}
	try {
		int curr_Motivation = teamsById.find(teamId)->gettotalMotivation();
		teamsById.remove( teamId );
		MotivationKey curr_team_motivation_key = MotivationKey(curr_Motivation,
			teamId);
		teamsByMotivation.remove(curr_team_motivation_key);

		return  StatusType::SUCCESS;
	} catch (const std::bad_alloc&) {
		return  StatusType::ALLOCATION_ERROR;
	}
}

StatusType Racenion::add_contestant(int contestantId,
                                    int teamId,
                                    const Skill &skill,
                                    int motivation,
                                    int missionsHad)
{
	if((teamId<= 0 || contestantId <= 0 || motivation < 0 || missionsHad < 0
|| !skill.isValid() )) {

		return StatusType::INVALID_INPUT;
	}
	try {
		Team* temp_team = teamsById.find(teamId);
		if(!temp_team  ) {
			return  StatusType::FAILURE;
		}
		// write your codee here

		//
	} catch  (const std::bad_alloc&) {
		return  StatusType::ALLOCATION_ERROR;
	}

}

output_t<int> Racenion::duel(int teamId1, int teamId2) {
// WE NEED to add all constant  missionsHad
	if(teamId1 <= 0  || teamId2 <= 0 || (teamId1 == teamId2) ) {
		return  StatusType::INVALID_INPUT ;
	}
	try {
		Team* temp_team1 = teamsById.find(teamId1);
		Team* temp_team2 = teamsById.find(teamId2);
		if(!temp_team1 || !temp_team2 ) {
			return StatusType::FAILURE;
		}
		if(temp_team1) {
			if(temp_team1->isEmpty()) {
				return StatusType::FAILURE;
			}
		}
		if(temp_team2) {
			if(temp_team2->isEmpty()) {
				return StatusType::FAILURE;
			}
		}
		int first_team_power = temp_team1->gettotalMotivation() + temp_team1->getTeamExp();
		int second_team_power = temp_team2->gettotalMotivation() + temp_team2->getTeamExp();
		if(first_team_power == second_team_power) {
			Skill* first_team_skill = temp_team1->getTeamSkills();
			Skill* second_team_skill = temp_team2->getTeamSkills();
			if(first_team_skill == second_team_skill) {
				temp_team1->addExp(1);
				temp_team1->addExp(1);
			return  0 ;	//draw
			}
			if( first_team_skill > second_team_skill ) {
				temp_team1->addExp(3);
				return  2 ;  //FIRST_WON_SKILL,
			} else {
				temp_team2->addExp(3);
				return  4 ; //SECOND_WON_SKILL
			}
		} else {
			if( first_team_power > second_team_power ) {
				temp_team1->addExp(3);
				return  1 ;  //FIRST_WON_POWERL,
			} else {
				temp_team1->addExp(3);
				return  3 ; //SECOND_WON_POWER
			}
		}

	}catch  (const std::bad_alloc&) {
		return  StatusType::ALLOCATION_ERROR;
	}
	return 0;
}

output_t<int> Racenion::get_contestant_missions_number(int contestantId) {
	return 0;
}

output_t<int> Racenion::get_team_experience(int teamId) {
	if(teamId <=0 ) {
		return  StatusType::INVALID_INPUT;
	}
	try {

	Team* temp_team = teamsById.find(teamId);
	if(temp_team  ) {
		return temp_team->getTeamExp();
	} else {
		return  StatusType::FAILURE;
	}
	} catch (const std::bad_alloc&) {
		return  StatusType::ALLOCATION_ERROR;
	}
	return 0;
}

output_t<int> Racenion::get_ith_collective_motivation_team(int i) {
	if( i <= 0 || i > teamsById.getSize() ) {
   return 	StatusType::FAILURE;
	}
	try {
		return teamsByMotivation.findByRank(i).get()->key.teamId ;
		// return two things ?? id or status or both// answer it dose manully
	} catch (const std::bad_alloc&) {
		return  StatusType::ALLOCATION_ERROR;
	}
	return 0;
}

output_t<Skill> Racenion::get_partial_team_skill(int contestantId) {
	return Skill();
}

StatusType Racenion::recruit(int recruitingTeamId, int recruitedTeamId) {
	if(recruitingTeamId <= 0  || recruitingTeamId <= 0 || (recruitingTeamId == recruitedTeamId) ) {
		return  StatusType::INVALID_INPUT ;
	}
	try {
		Team* temp_team1 = teamsById.find(recruitingTeamId);
		Team* temp_team2 = teamsById.find(recruitedTeamId);
		if(!temp_team1 || !temp_team2 ) {
			return StatusType::FAILURE;
		}

		// write your code here 
	} catch  (const std::bad_alloc&) {
		return  StatusType::ALLOCATION_ERROR;
	}
}
