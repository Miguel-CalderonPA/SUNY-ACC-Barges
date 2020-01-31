# SUNY-ACC-Barges
A simulation of the barges floating down a river, inspired by the incident in update NY, where six barges came loose and started floating down the Hudson River.
Article: https://www.lohud.com/story/news/local/westchester/2018/03/02/barges-spotted-floating-loose-river-off-irvington-reports/389648002/

- 3-D array as the river
- Barges must survive through obstacles and the banks or they loose health
- Each boat has an assigned starting position, cost, name, health
- River & Barges data are from input files
- if the barge is less than half health it starts sinking
- The damage cost is also calculated
  - each ship's lost health * the hullcost + the ship cost (per ship)
  
