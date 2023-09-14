#ifndef ELECTION_RESULTS
#define ELECTION_RESULTS

#include "parse_district_info.h"
#include "parse_election_results.h"
#include "result_types.h"
#include "country_vote_bar.h"
#include "dhondt.h"
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <cassert>

std::map<std::string, int> GetElectionResults(
    const std::map<std::string, int> &district_seats,
    ElectionResults *er) {
  std::map<std::string, int> results;
  std::map<std::string, bool> bar = PassesBar(er);
  assert(er != nullptr);
  for (auto D : er->ByDistrict()) {
    std::string district = D.first;
    assert(district_seats.find(district) != district_seats.end());
    auto filtered_votes = FilterParties(D.second.VoteCountByParty(), bar);
    auto seat_counts = VotesToMandates(
        filtered_votes, district_seats.find(district)->second);
    for (auto R : seat_counts) {
      results[R.first] += R.second;
    }
  }
  return results;
}

#endif // ELECTION_RESULTS
