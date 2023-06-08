#include "trojanmap.h"

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return
 * -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string &id) { 
  if (data.find(id) == data.end()) return -1;
  else return data[id].lat;
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist,
 * return -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string &id) {
  if (data.find(id) == data.end()) return -1;
  else return data[id].lon;
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return
 * "NULL".
 *
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string &id) {
  if (data.find(id) == data.end()) return "NULL";
  else return data[id].name;
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return
 * an empty vector.
 *
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string &id) {
  if (data.find(id) == data.end()) return {};
  else return data[id].neighbors;
}

/**
 * GetID: Given a location name, return the id.
 * If the node does not exist, return an empty string.
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
void TrojanMap::CreateNameIdMapping(){
 for(auto loc : data){
   name_to_id[loc.second.name] = loc.first;
 }
}
 
std::string TrojanMap::GetID(const std::string &name) {
std::string res = "";
if (name_to_id.find(name) == name_to_id.end()) return "";
 return name_to_id[name];
}


/*std::string TrojanMap::GetID(const std::string &name) {
  std::string res = "";
  for(auto m : data){
    if(m.second.name == name) {
      res = m.second.id;
      break;
    }
  }
  return res;
}*/

/**
 * GetPosition: Given a location name, return the position. If id does not
 * exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> results(-1, -1);
  for(auto m : data){
    if(m.second.name == name) {
      results = std::make_pair(m.second.lat, m.second.lon);
      break;
    }  
  }
  return results;
}

/**
 * CalculateEditDistance: Calculate edit distance between two location names
 *
 */
int TrojanMap::CalculateEditDistance(std::string a, std::string b) {     
  int len_a = a.length();
  int len_b = b.length();

  int dist[2][len_a + 1];
  //fill the dist array with 0
  memset(dist, 0, sizeof dist);
  for(int i = 0; i <= len_a; i++) dist[0][i] = i;
  //start filling dist, this loop iterates every character b
  for(int i = 1; i <= len_b; i++){
    //this loop compares the character from the b with a 
    for(int j = 0; j <= len_a; j++){
      if(j == 0) dist[i%2][j] = i;
      else if (a[j - 1] == b[i - 1]) dist[i%2][j] = dist[(i - 1)%2][j - 1];
      else dist[i%2][j] = 1 + std::min(dist[(i-1)%2][j], 
                                       std::min(dist[i%2][j-1], dist[(i-1)%2][j - 1]));
    }
  }
  return dist[len_b % 2][len_a];
}

/**
 * FindClosestName: Given a location name, return the name with smallest edit
 * distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : similar name
 */
std::string TrojanMap::FindClosestName(std::string name) {
  std::string tmp = ""; // Start with a dummy word
  std::map<std::string, int> name_dist;
  //calculate every edit distance for the name inside the data
  for(auto m : data){
    tmp = m.second.name;
    if(name_dist.count(tmp) < 1){
      name_dist[tmp] = TrojanMap::CalculateEditDistance(name, tmp);
    }
  }
  //loop to get the name of the minimum edit dist inside the data
  std::pair<std::string, int> min_dist("KFC", INT_MAX);
  for(auto m : name_dist){
    if(m.second < min_dist.second){
      min_dist.first = m.first;
      min_dist.second = m.second;
    }
  }
  return min_dist.first;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name) {
  std::vector<std::string> results;
  //remove all the blank inside the name 
  name.erase(remove(name.begin(), name.end(), ' '), name.end());
  //lower all the characters in the name
  std::string lowername = "";
  lowername.resize(name.size());
  std::transform(name.begin(), name.end(), lowername.begin(), ::tolower);

  //traverse the map name
  for(auto m : data){
    std::string mapname = m.second.name;
    std::string maplowername = "";
    maplowername.resize(mapname.size());
    std::transform(mapname.begin(), mapname.end(), maplowername.begin(), ::tolower);
    //find the give char as the perfix of the element in map
    if(maplowername.find(lowername) == 0) results.push_back(mapname);
  }
  return results;
}

/**
 * GetAllCategories: Return all the possible unique location categories, i.e.
 * there should be no duplicates in the output.
 *
 * @return {std::vector<std::string>}  : all unique location categories
 */
std::vector<std::string> TrojanMap::GetAllCategories() {
  std::set<std::string> set_categories;
  for(auto m : data){
    for(auto it = m.second.attributes.begin(); it != m.second.attributes.end(); ++it){
      set_categories.insert(*it);
    }
  }

  std::vector<std::string> vec_categories;
  for(auto it = set_categories.begin(); it != set_categories.end(); ++it){
    vec_categories.push_back(*it);
  }
  return vec_categories;
}

/**
 * GetAllLocationsFromCategory: Return all the locations of the input category (i.e.
 * 'attributes' in data.csv). If there is no location of that category, return
 * (-1, -1). The function should be case-insensitive.
 *
 * @param  {std::string} category          : category name (attribute)
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetAllLocationsFromCategory(std::string category) {    
  std::vector<std::string> res;
  std::string lowercategory = "";
  lowercategory.resize(category.size());
  std::transform(category.begin(), category.end(), lowercategory.begin(), ::tolower);
  for(auto m : data){
    for(auto it = m.second.attributes.begin(); it != m.second.attributes.end(); ++it){
      if(lowercategory == *it) res.push_back(m.second.id);
    }
  }
  return res;
}

/**
 * GetLocationRegex: Given the regular expression of a location's name, your
 * program should first check whether the regular expression is valid, and if so
 * it returns all locations that match that regular expression.
 *
 * @param  {std::regex} location name      : the regular expression of location
 * names
 * @return {std::vector<std::string>}     : ids
 */
//.?da.{1,10}
//Ra.?ph.+
std::vector<std::string> TrojanMap::GetLocationRegex(std::regex location) {
  std::vector<std::string> ids = {};
  for(auto m : data){
    if(m.second.name != ""){
      if(std::regex_match(m.second.name, location) == 1) ids.push_back(m.second.id);
    }
  }
  return ids;
}

/**
 * CalculateDistance: Get the distance between 2 nodes.
 *
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id,
                                    const std::string &b_id) {
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2), 2.0) + cos(a.lat * M_PI / 180.0) *
                                           cos(b.lat * M_PI / 180.0) *
                                           pow(sin(dlon / 2), 2.0);
  double c = 2 * asin(std::min(1.0, sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations
 * inside the vector.
 *
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0; i < int(path.size()) - 1; i++) {
    sum += CalculateDistance(path[i], path[i + 1]);
  }
  return sum;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path
 * which is a list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {

    std::vector<std::string> path;
    std::string start = GetID(location1_name);
    std::string goal = GetID(location2_name);
    if(start == "" || goal == "") return {""};
    else{
    std::priority_queue <std::pair<double,std::string>,
                         std::vector<std::pair<double,std::string>>,
                         std::greater<std::pair<double,std::string>>> min_dist;  //<distance, id>
    
    std::unordered_map <std::string,double> dist;  //from start to thte current location
    for(auto m : data){
      dist[m.second.id] = DBL_MAX;
    }
    dist[start] = 0;
    min_dist.push(std::make_pair(dist[start],start));

    std::unordered_map <std::string,std::string> calculated_loca;  //record the id of the calculated location
    std::unordered_map <std::string,bool> assigment;  //record whether the location where have been assigned the distance
    for(auto m : data){
      assigment[m.second.id] = false;
    }
 
    while(!min_dist.empty()){
      std::string current = min_dist.top().second;
      min_dist.pop();
      if(current != goal){
        if(CalculateDistance(current,start)>dist[current]) continue;
        else if(assigment[current]) continue;
        else{
          assigment[current] = true;
          for(auto neighbour : data[current].neighbors){
            double updateddist = dist[current] + CalculateDistance(current,neighbour);
             if(dist[neighbour]>updateddist){
               dist[neighbour] = updateddist;
               calculated_loca[neighbour] = current;   
               min_dist.push(std::make_pair(dist[neighbour],neighbour));          
            }
          }
        }
      }
      else{
      assigment[goal] = true;
      break;
      }
    }

    for(auto loca = goal; loca != start; loca = calculated_loca[loca])
    {
      path.push_back(loca);
    }
    path.push_back(start);
    std::reverse(path.begin(),path.end());
    }


  return path;
}


std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
  std::string location1_name, std::string location2_name) {
 
  std::vector<std::string> path;
 
  std::string start_id = GetID(location1_name);
  std::string goal_id = GetID(location2_name);
  if(start_id == "" || goal_id == ""){
    return path;
  }
 
  // initialize distance
  // dist_map {id : distance}
  std::map<std::string, double> distance;
  std::map<std::string, std::string> parent;
  for(std::pair<std::string, Node> cur : data){
    std::string cur_id = cur.first;
    distance[cur_id] = INT_MAX;
    parent[cur_id] = cur_id;
  }
 
  // initialize the start node
  distance[start_id] = 0;
 
 
  // release edges
  for(int cnt = 0; cnt < data.size() - 1; cnt++){
    bool is_updated = false;
 
    // iterate all vertices
    for(std::pair<std::string, Node> cur : data){
      std::string cur_id = cur.first;
      if(distance[cur_id] == INT_MAX){
         continue;
      }
 
      std::vector<std::string> neighbor_ids = GetNeighborIDs(cur_id);
 
      // iterate all the edges of each vertex
      for(std::string neighbor_id : neighbor_ids){
 
        // update distance info
        double cur_distance = distance[cur_id] + CalculateDistance(cur_id, neighbor_id);
        if(cur_distance < distance[neighbor_id]){
          distance[neighbor_id] = cur_distance;
          parent[neighbor_id] = cur_id;
          is_updated = true;
        }
      }
    }
 
    // check the condition
    if(!is_updated){
     
      // add id to the path.
      std::string prev_id = goal_id;
      path.push_back(prev_id);
      while(parent[prev_id] != start_id){
        path.push_back(parent[prev_id]);
        prev_id = parent[prev_id];
      }
      path.push_back(start_id);
      std::reverse(path.begin(), path.end());
      return path;
   }
  }
  return path;
}
 

/**
 * Traveling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
 
 void dfs_Brute_force(int cur_idx, int num, double cur_distance,std::vector<std::string> &location_ids,
std::vector<std::string> &path, std::pair<double, std::vector<std::vector<std::string>>> &records,
std::vector<bool> &visited, TrojanMap &m,std::vector<std::string> &shortest_path){
 if(num >= location_ids.size()){
   path.push_back(location_ids[cur_idx]);
 
   // append the starting location.
   path.push_back(path[0]);
   records.second.push_back(path);
 
   // update shortest path
   double shortest_distance = cur_distance + m.CalculateDistance(location_ids[cur_idx], path[path.size() - 1]);
   if(records.first > shortest_distance){
     records.first = shortest_distance;
     shortest_path = path;
   }
 
   path.pop_back();
   path.pop_back();
   return;
 }
 
 visited[cur_idx] = true;
 path.push_back(location_ids[cur_idx]);
 for(int i = 0; i < location_ids.size(); i++){
   if(!visited[i]){
     dfs_Brute_force(i, num + 1, cur_distance + m.CalculateDistance(location_ids[cur_idx], location_ids[i]), location_ids, path, records, visited, m, shortest_path);
   }
 }
 path.pop_back();
 visited[cur_idx] = false;
}

 
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Brute_force(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
 TrojanMap m;
 records.first = DBL_MAX;
 std::vector<std::string> shortest_path;
 for(int i = 0; i < location_ids.size(); i++){
   std::vector<bool> visited;
   std::vector<std::string> path;
   visited.resize(location_ids.size(), false);
   dfs_Brute_force(i, 1, 0, location_ids, path, records, visited, m, shortest_path);
 }
 records.second.push_back(shortest_path);
 
 return records;
}


void dfs_Backtracking(int cur_idx, int num, double cur_distance,double shortest_distance,std::vector<std::string> &location_ids,
std::vector<std::string> &path, std::pair<double, std::vector<std::vector<std::string>>> &records,
std::vector<bool> &visited, TrojanMap &m,std::vector<std::string> &shortest_path){
 if(cur_distance > shortest_distance){
   return;
 }
 
 if(num >= location_ids.size()){
   path.push_back(location_ids[cur_idx]);
 
   // append the starting location.
   path.push_back(path[0]);
   records.second.push_back(path);
 
   // update shortest path
   shortest_distance = cur_distance + m.CalculateDistance(location_ids[cur_idx], path[path.size() - 1]);
   if(records.first > shortest_distance){
     records.first = shortest_distance;
     shortest_path = path;
   }
 
   path.pop_back();
   path.pop_back();
   return;
 }
 
 visited[cur_idx] = true;
 path.push_back(location_ids[cur_idx]);
 for(int i = 0; i < location_ids.size(); i++){
   if(!visited[i]){
     dfs_Backtracking(i, num + 1, cur_distance + m.CalculateDistance(location_ids[cur_idx], location_ids[i]), shortest_distance, location_ids, path, records, visited, m, shortest_path);
   }
 }
 path.pop_back();
 visited[cur_idx] = false;
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
 TrojanMap m;
 records.first = DBL_MAX;
 std::vector<std::string> shortest_path;
 double shortest_distance = DBL_MAX;
 for(int i = 0; i < location_ids.size(); i++){
   std::vector<bool> visited;
   std::vector<std::string> path;
   visited.resize(location_ids.size(), false);
   dfs_Backtracking(i, 1, 0, shortest_distance,location_ids, path, records, visited, m, shortest_path);
 }
 records.second.push_back(shortest_path);
 return records;

}

// Hint: https://en.wikipedia.org/wiki/2-opt
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_2opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  //init the path
  std::vector<std::string> currentpath = location_ids;
  currentpath.push_back(location_ids[0]);
  //2_opt
  bool isshorter = true;
  while(isshorter){
    loop:
    isshorter = false;
    double currentdist = CalculatePathLength(currentpath);
    for(int i = 1; i <= location_ids.size() - 2; i++){
      for(int j = i + 1; j <= location_ids.size() - 1; j++){
        //reverse the chosen part of path
        std::vector<std::string> newpath = currentpath;
        std::reverse(newpath.begin() + i, newpath.begin() + j + 1);
        double newdist = CalculatePathLength(newpath);
        if(newdist < currentdist){
          isshorter = true;
          //update path
          currentdist = newdist;
          currentpath = newpath;
          //output
          records.first = currentdist;
          records.second.push_back(currentpath);
          goto loop;
        }
      }
    }
  }
  return records;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(
    std::string locations_filename) {
  std::vector<std::string> location_names_from_csv;
  std::fstream fin;
  fin.open(locations_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, word)) {
    location_names_from_csv.push_back(word);
  }
  fin.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(
    std::string dependencies_filename) {
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream fin;
  fin.open(dependencies_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);
    std::vector<std::string> dependency;
    while (getline(s, word, ',')) {
      dependency.push_back(word);
    }
    dependencies_from_csv.push_back(dependency);
  }
  fin.close();
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a
 * sorting of nodes that satisfies the given dependencies. If there is no way to
 * do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     :
 * prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
 
 bool topo_sort(std::string cur, std::map<std::string, std::vector<std::string>> &graph,
std::map<std::string, int> &visit_status, std::vector<std::string> &result){
 // status
 const int UNVISITED = 0;
 const int VISITING = 1;
 const int VISITED = -1;
 // base case
 if(visit_status[cur] == VISITING){
   return true;
 }
 
 if(visit_status[cur] == VISITED){
   return false;
 }
 
 visit_status[cur] = VISITING;
 std::vector<std::string> nexts = graph[cur];
 
 if(nexts.size() != 0){
   for(std::string next : nexts){
     if(topo_sort(next, graph, visit_status, result)){
       return true;
     }
   }
 }
 visit_status[cur] = VISITED;
 result.push_back(cur);
 
 return false;
}

 
std::vector<std::string> TrojanMap::DeliveringTrojan(
    std::vector<std::string> &locations,
    std::vector<std::vector<std::string>> &dependencies) {
  std::map<std::string, int> visit_status;
  for(auto location : locations){
    visit_status[location] = 0;
  }
 // build graph
  std::map<std::string, std::vector<std::string>> graph;
  for(int i = 0; i < dependencies.size(); i++){
    std::vector<std::string> row = dependencies[i];
    std::string from_v = row[0];
    for(int j = 1; j < row.size(); j++){
      std::string to_v = row[j];
      graph[from_v].push_back(to_v);
    }
  }
  std::vector<std::string> result;
  for(auto location : locations){
    topo_sort(location, graph, visit_status, result);
  }
  std::reverse(result.begin(), result.end());
  return result;  
}

/**
 * inSquare: Give a id retunr whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square) {
 // id doesn't exist
 if(data.find(id) == data.end()){
   return false;
 }
 // Get the range
 double left_bound = square[0];
 double right_bound = square[1];
 double upper_bound = square[2];
 double lower_bound = square[3];
 return GetLon(id) >= left_bound && GetLon(id) <= right_bound && GetLat(id) <= upper_bound && GetLat(id) >= lower_bound;
}


/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location
 * ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square
 * area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the
 * square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square) {
 // include all the nodes in subgraph
 std::vector<std::string> subgraph;
 // Iterate all the ids.
 for(std::pair<std::string, Node> cur : data){
   std::string cur_id = cur.first;
   // If in square, add it to subgraph.
   if(inSquare(cur_id, square)){
     subgraph.push_back(cur_id);
   }
 }
 return subgraph;
}


/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true
 * if there is a cycle path inside the square, false otherwise.
 *
 * @param {std::vector<std::string>} subgraph: list of location ids in the
 * square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
 
 
bool contains_cycle(std::string cur, std::string parent, std::map<std::string, std::vector<std::string>> &graph, std::map<std::string, int> &visit_status){
 // status
 const int UNVISITED = 0;
 const int VISITING = 1;
 const int VISITED = -1;
 // base case
 if(visit_status[cur] == VISITING){
   return true;
 }
 
 if(visit_status[cur] == VISITED){
   return false;
 }
 
 visit_status[cur] = VISITING;
  std::vector<std::string> nexts = graph[cur];
 
 if(nexts.size() != 0){
   for(std::string next : nexts){
     if(next == parent){
       continue;
     }
     if(contains_cycle(next, cur, graph, visit_status)){
       return true;
     }
   }
 }
 visit_status[cur] = VISITED;
 return false;
}

bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square) {
 // initialize status
 int UNVISITED = 0;
 int VISITED = -1;
 // Build the graph, {id : neighbour_ids}.
 std::map<std::string, std::vector<std::string>> graph;
 std::map<std::string, int> visit_status;
 // Iterate all the vertex in subgraph
 for(std::string cur_id : subgraph){
 
   // Iterate the edges of each vertex.
   graph[cur_id] = {};
   visit_status[cur_id] = UNVISITED;
 
   for(std::string neighbour_id : GetNeighborIDs(cur_id)){
 
     // Add edges in square into graph.
     if(inSquare(neighbour_id, square)){
       graph[cur_id].push_back(neighbour_id);
       //visit_status[neighbour_id] = UNVISITED;
      
     }
   }
 }
  // dfs
 for(std::string cur_id : subgraph){
   if(visit_status[cur_id] == VISITED){
     continue;
   }
   if(contains_cycle(cur_id, cur_id, graph, visit_status)){
     return true;
   }
 }
  return false;
}
 



 


/**
 * FindNearby: Given a class name C, a location name L and a number r,
 * find all locations in class C on the map near L with the range of r and
 * return a vector of string ids
 *
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {int} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k) {
  std::vector<std::string> res;
 // get id in the range
 std::string center_id = GetID(name);
 std::vector<std::string> point_ids = GetAllLocationsFromCategory(attributesName);
  // comparator
 auto cmp = [](const std::pair<std::string, double> &p1, const std::pair<std::string, double> &p2) -> bool{return p1.second < p2.second;};
 std::priority_queue<std::pair<std::string, double>, std::vector<std::pair<std::string, double>>,decltype(cmp)> max_heap(cmp);
 
 // push into heap
 for(std::string point_id : point_ids){
   double dist = CalculateDistance(point_id, center_id);
   if(dist <= r && point_id != center_id){
     max_heap.push(std::make_pair(point_id, dist));
     if(max_heap.size() > k){
       max_heap.pop();
     }
   }
 }
 
 // sorted
 while(!max_heap.empty()){
   res.push_back(max_heap.top().first);
   max_heap.pop();
 }
 std::reverse(res.begin(), res.end());
 return res;

}

/**
 * Shortest Path to Visit All Nodes: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of
 * total distance and the all the progress to get final path
 */
void dfs(int level, std::vector<std::string> &path, std::vector<bool> &visited, std::vector<std::vector<std::string>> &res, std::vector<std::string> &location_names){
 
   if(level >= visited.size() + 1){
     std::vector<std::string> temp(path);
     res.push_back(temp);
     return;
   }
 
   for(int i = 0; i < visited.size(); i++){
     if(visited[i]){
         continue;
     }
     path.push_back(location_names[i]);
     visited[i]=true;
     dfs(level + 1,path,visited, res, location_names);
     path.pop_back();
     visited[i] = false;
   }
 
 }
 
std::vector<std::vector<std::string>> permute(std::vector<std::string> &location_names, TrojanMap &m) {
 
 // names
 std::vector<std::vector<std::string>> permutation;
 
 // name
 std::vector<std::string> path;
 std::vector<bool> visited;
 visited.resize(location_names.size(), false);
 dfs(1, path, visited, permutation, location_names);
 return permutation;
}
 
std::vector<double> calculate_paths_distance(std::vector<std::vector<std::string>> &paths_ids, TrojanMap &m){
 std::vector<double> paths_distance;
 for(int i = 0; i < paths_ids.size(); i++){
 
   double path_distance = 0;
   for(int j = 0; j < paths_ids[i].size() - 1; j++){
     path_distance += m.CalculateDistance(paths_ids[i][j], paths_ids[i][j + 1]);
   }
 
   paths_distance.push_back(path_distance);
 }
 
 return paths_distance;
}
 
std::vector<std::string> TrojanMap::TrojanPath(std::vector<std::string> &location_names) {
 TrojanMap m;
 // get permutation, names
 std::vector<std::vector<std::string>> permutation = permute(location_names, m);
 std::vector<std::string> res;
 
 // ids
 std::vector<std::vector<std::string>> paths_ids;
 
 // calculate distance
 for(int i = 0; i < permutation.size(); i++){
   std::vector<std::string> path_ids;
   for(int j = 0; j < permutation[i].size() - 1; j++){
     std::string start = permutation[i][j];
     std::string goal = permutation[i][j + 1];
 
     //std::cout << i << "," << j <<std::endl;
     std::vector<std::string> step_ids  = m.CalculateShortestPath_Dijkstra(start, goal);
 
     //deduplicate
     step_ids.pop_back();
     for(auto step_id : step_ids){
       path_ids.push_back(step_id);
     }
   }
 
   // append the last location
   path_ids.push_back(m.GetID(permutation[i][permutation[i].size() - 1]));
   paths_ids.push_back(path_ids);
 }
 
 //select the minimal distance
 std::vector<double> paths_distance = calculate_paths_distance(paths_ids, m);
 
 double min_distance = DBL_MAX;
  for(int i = 0; i < paths_distance.size(); i++){
   if(paths_distance[i] < min_distance){
     min_distance = paths_distance[i];
     res = paths_ids[i];
   }
 }
 std::reverse(res.begin(), res.end());
 return res;
}


/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 *
 */
void TrojanMap::CreateGraphFromCSVFile() {
  // Do not change this function
  std::fstream fin;
  fin.open("src/lib/data.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        if (isalpha(word[0])) n.attributes.insert(word);
        if (isdigit(word[0])) n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}
