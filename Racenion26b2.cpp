// You can edit anything you want in this file.
// However, you need to implement all public Racenion functions, which are provided below as a template.

#include "Racenion26b2.h"

Racenion::Racenion() {}

Racenion::~Racenion() {}

StatusType Racenion::add_team(int teamId) {
	return StatusType::FAILURE;
}

StatusType Racenion::remove_team(int teamId) {
	return StatusType::FAILURE;
}

StatusType Racenion::add_contestant(int contestantId,
                                    int teamId,
                                    const Skill &skill,
                                    int motivation,
                                    int missionsHad)
{
	// checks valediction of inputs
	if (contestantId <=0 || teamId <=0 || !skill.isValid() ||
		motivation < 0 || missionsHad < 0) {
		return StatusType::INVALID_INPUT;
	}

	// checks if the contestant is not already in, and the team is found
	if (uf.isFound(contestantId) || teamsById.search(teamId) == false) {
		return StatusType::FAILURE;
	}

	try {
		// adds the new contestant to the hash table (O(1) in average)
		uf.addContestantUF(contestantId, teamId, skill, motivation, missionsHad);

		// add him to the relevant team (and maintain the changes)
		auto teamPtr = teamsById.find(teamId);   // O(log(k))
		teamPtr->addContestantToTeam(uf.getContestantPtr(contestantId));
	}
	catch (std::bad_alloc& er) {
		return StatusType::ALLOCATION_ERROR;
	}

	return StatusType::SUCCESS;
}

output_t<int> Racenion::duel(int teamId1, int teamId2) {
	return 0;
}

output_t<int> Racenion::get_contestant_missions_number(int contestantId) {
	return 0;
}

output_t<int> Racenion::get_team_experience(int teamId) {
	return 0;
}

output_t<int> Racenion::get_ith_collective_motivation_team(int i) {
	return 0;
}

output_t<Skill> Racenion::get_partial_team_skill(int contestantId) {
	return Skill();
}

StatusType Racenion::recruit(int recruitingTeamId, int recruitedTeamId) {
	return StatusType::FAILURE;
}
