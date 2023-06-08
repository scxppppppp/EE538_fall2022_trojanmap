#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

TEST(TrojanMapTest, TSP_brute_force) {
  TrojanMap m;
  
  std::vector<std::string> input{"1873056015", "6905329551", "213332060", "1931345270"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1873056015", "213332060", "1931345270", "6905329551", "1873056015"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back()) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSP_brute_force_2) {
  TrojanMap m;
  
  std::vector<std::string> input{"1862312636", "7424270441", "67666219", "4015405548", "4015203110", "6807439002"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1862312636", "4015405548", "4015203110", "6807439002", "7424270441", "67666219", "1862312636"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back()) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSP) {
  TrojanMap m;
  
  std::vector<std::string> input{"1873056015", "6905329551", "213332060", "1931345270"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1873056015", "213332060", "1931345270", "6905329551", "1873056015"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
 if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSP2) {
  TrojanMap m;
  
  std::vector<std::string> input{"1862312636", "7424270441", "67666219", "4015405548", "4015203110", "6807439002"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1862312636", "4015405548", "4015203110", "6807439002", "7424270441", "67666219", "1862312636"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back()) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSP_2opt) {
  TrojanMap m;
  
  std::vector<std::string> input{"1873056015", "6905329551", "213332060", "1931345270"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1873056015", "213332060", "1931345270", "6905329551", "1873056015"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSP_2opt_2) {
  TrojanMap m;
  
  std::vector<std::string> input{"1862312636", "7424270441", "67666219", "4015405548", "4015203110", "6807439002"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1862312636", "4015405548", "4015203110", "6807439002", "7424270441", "67666219", "1862312636"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back()) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}

// copied below, just for ease of points assignment
TEST(TrojanMapTest, TSP_2opt_3) {
  TrojanMap m;
  
  std::vector<std::string> input{"1862312636", "7424270441", "67666219", "4015405548", "4015203110", "6807439002"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1862312636", "4015405548", "4015203110", "6807439002", "7424270441", "67666219", "1862312636"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back()) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSP_2opt_4) {
  TrojanMap m;
  
  std::vector<std::string> input{"1862312636", "7424270441", "67666219", "4015405548", "4015203110", "6807439002"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1862312636", "4015405548", "4015203110", "6807439002", "7424270441", "67666219", "1862312636"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back()) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, FindNearby) {
  TrojanMap m;
  
  auto result = m.FindNearby("supermarket", "Ralphs", 10, 10);
  std::vector<std::string> ans{"5237417649", "6045067406", "7158034317"};
  EXPECT_EQ(result, ans);
}

TEST(TrojanMapTest, FindNearby2) {
  TrojanMap m;
  
  auto result = m.FindNearby("place_of_worship", "Target", 5, 5);
  std::vector<std::string> ans{"358850010", "358850041", "358826562", "358850068", "358850076"};
  EXPECT_EQ(result, ans);
}
// Test CalculateShortestPath_TrojanPath function
TEST(TrojanMapTest, TrojanPath) {
  TrojanMap m;
  
  // Test for Ralphs, KFC and Chick-fil-A 
  std::vector<std::string> input = {"KFC", "Ralphs", "Chick-fil-A"};
  auto path = m.TrojanPath(input);
  std::vector<std::string> gt{
      "2578244375","4380040154","4380040158","4380040167","6805802087","8410938469","6813416131",
      "7645318201","6813416130","6813416129","123318563","452688940","6816193777","123408705",
      "6816193774","452688933","452688931","123230412","6816193770","6787470576","4015442011",
      "6816193692","6816193693","6816193694","3398621886","3398621887","6816193695","5690152756",
      "6804883324","3398621888","6813416123","6813416171","6807536647","6807320427","6807536642",
      "6813416166","7882624618","7200139036","122814440","6813416163","7477947679","7298150111",
      "6787803640","6807554573","2613117890","4835551096","4835551101","4835551097","4835551100",
      "3088547686","4835551100","4835551099","4835551098","6813565307","6813565306","6813565305",
      "6813565295","6813565296","3402814832","4835551107","6813379403","6813379533","3402814831",
      "6813379501","3402810298","6813565327","3398574883","6813379494","6813379495","6813379544",
      "6813379545","6813379536","6813379546","6813379547","6814916522","6814916523","1732243620",
      "4015372469","4015372463","6819179749","1732243544","6813405275","348121996","348121864",
      "6813405280","1472141024","6813411590","216155217","6813411589","1837212103","1837212101",
      "6814916516","6814916515","6820935910","4547476733"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  input = {"Ralphs", "Chick-fil-A", "KFC"};
  path = m.TrojanPath(input);
  EXPECT_EQ(path, gt);

  input = {"Ralphs", "KFC", "Chick-fil-A"};
  path = m.TrojanPath(input);
  EXPECT_EQ(path, gt);

}

