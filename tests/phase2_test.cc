#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

// Test CalculateEditDistance function
TEST(TrojanMapTest, CalculateEditDistance) {
  TrojanMap m;
  EXPECT_EQ(m.CalculateEditDistance("horse", "ros"), 3);
  EXPECT_EQ(m.CalculateEditDistance("intention", "execution"), 5);
  EXPECT_EQ(m.CalculateEditDistance("dough", "cough"), 1);
  EXPECT_EQ(m.CalculateEditDistance("bail", "bale"), 2);
  EXPECT_EQ(m.CalculateEditDistance("welcome", "composition"), 10);
}


// Test FindClosestName function
TEST(TrojanMapTest, FindClosestName) {
  TrojanMap m;
  EXPECT_EQ(m.FindClosestName("Rolphs"), "Ralphs");
  EXPECT_EQ(m.FindClosestName("Targeety"), "Target");
  EXPECT_EQ(m.FindClosestName("Chiotttle"), "Chipotle");
  EXPECT_EQ(m.FindClosestName("Chaserr"), "Chase");
  EXPECT_EQ(m.FindClosestName("Chevrxn"), "Chevron");
}


// Test get all categories
TEST(TrojanMapTest, GetAllCategories) {
  TrojanMap m;
  
  auto output = m.GetAllCategories();
  std::set<std::string> expected = {
    "artwork", "attraction", "bakery", "bank", "bar", "beauty", "beverages", "bicycle", "bicycle_rental",
    "bus_station", "cafe", "car", "car_repair", "car_wash", "charging_station", "childcare", "clinic",
    "clothes", "confectionery", "convenience", "copyshop", "dentist", "department_store", "driving_school",
    "fabric", "fast_food", "food_court", "fountain", "fuel", "gallery", "hairdresser", "hospital", "hotel",
    "library", "marketplace", "mobile_phone", "museum", "music", "optician", "parcel_locker", "parking",
    "parking_entrance", "pharmacy", "place_of_worship", "police", "post_box", "post_office", "restaurant",
    "school", "shoe_repair", "shoes", "skate", "social_facility", "supermarket", "theatre", "tobacco",
    "yoga", "yes"
  };
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, expected);
}

TEST(TrojanMapTest, GetAllLocationsFromCategory) {
  TrojanMap m;
  
  auto output = m.GetAllLocationsFromCategory("bank");
  std::set<std::string> expected = {"9591449441", "5237417651", "9591449465"};
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, expected);
}

TEST(TrojanMapTest, GetAllLocationsFromCategory2) {
  TrojanMap m;
  
  auto output = m.GetAllLocationsFromCategory("supermarket");
  std::set<std::string> expected = {"5237417649", "2578244375", "7158034317", "6045067406"};
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, expected);
  }

TEST(TrojanMapTest, GetLocationRegex1) {
  TrojanMap m;
  std::set<std::string> expected_set;
  auto actual = m.GetLocationRegex(std::regex("dummy"));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(actual_set, expected_set);
}

TEST(TrojanMapTest, GetLocationRegex2) {
  TrojanMap m;
  std::set<std::string> expected_set = { "2578244375" };
  auto actual = m.GetLocationRegex(std::regex("Ra.?ph.+"));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(expected_set, actual_set);
}

TEST(TrojanMapTest, GetLocationRegex3) {
  TrojanMap m;
  std::set<std::string> expected_set = { "9596557990", "9596557987", "9462770200" };
  auto actual = m.GetLocationRegex(std::regex(".?da.{1,10}"));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(expected_set, actual_set);
}

// Test CalculateShortestPath_Dijkstra function 
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Chick-fil-A");
  std::vector<std::string> gt{
      "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920","6818427919",
      "6818427918","6818427892","6818427898","6818427917","6818427916","7232024780","6813416145",
      "6813416154","6813416153","6813416152","6813416151","6813416155","6808069740","6816193785",
      "6816193786","123152294","4015203136","4015203134","4015203133","21098539","6389467809",
      "4015203132","3195897587","4015203129","4015203127","6352865690","6813379589","6813379483",
      "3402887081","6814958394","3402887080","602606656","4872897515","4399697589","6814958391",
      "123209598","6787673296","122728406","6807762271","4399697304","4399697302","5231967015",
      "1862347583","3233702827","4540763379","6819179753","6820935900","6820935901","6813379556",
      "6820935898","1781230450","1781230449","4015405542","4015405543","1837212104","1837212107",
      "2753199985","6820935907","1837212100","4015372458","6813411588","1837212101","6814916516",
      "6814916515","6820935910","4547476733"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Dijkstra("Chick-fil-A", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Dijkstra function 
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra2) {
  TrojanMap m;
  
  auto path = m.CalculateShortestPath_Dijkstra("Target", "Chipotle");
  // Test from Target to Chipotle
  std::vector<std::string> gt{
      "5237417650","6814769289","6813379584","6813360961","6813379480","6813360960","6814620882","6813360954","6813360952","6813379420",
      "6813360951","6813360936","6813379467","6813379466","6813379465","6813379464","3402887075","6813379432","4536989637","4536989640",
      "3443310465","6813379491","6818390136","3433701978","4536989636","3432332948","6814770351","3431300454","4536993735","6814770342",
      "2776870272","5580882852","6814770345","2776870269","1472141961","5580883117","123153544","1673645147","2738332818","1673644724",
      "2738332817","122844997","5580881629","4399697303","4399697301","4399697300","6813379550","6814916523","1732243620","4015372469",
      "4015372463","6819179749","1732243544","6813405275","348121996","348121864","6813405280","1472141024","6813411590","216155217",
      "6820935908","9446678100","732641023"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Chipotle to Target
  path = m.CalculateShortestPath_Dijkstra("Chipotle", "Target");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Dijkstra 
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra3) {
  TrojanMap m;
  
  auto path = m.CalculateShortestPath_Dijkstra("Popeyes", "Target");
  // Test from Popeyes to Target
  std::vector<std::string> gt{
    "5695236164","4835551075","3403035506","5680945537","6814916550","3398621871","6813565323","3403035498","6816193705","5556118325",
    "5680945525","7693467754","3403035499","3403035500","7863689394","7863689395","4835551084","2613117900","3403034586","4835551093",
    "2613117862","3403034590","2613117890","2613117915","4835551105","6813565334","2613117867","6787803635","6807905595","6813379406",
    "2613117879","3398578893","3398574892","6813565290","3398578898","6813379398","6813379505","6813379519","4399698005","3398578900",
    "4399698015","6813379425","3398578901","6813379479","6813379584","6814769289","5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Target to Popeyes
  path = m.CalculateShortestPath_Dijkstra("Target", "Popeyes");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Dijkstra function
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "Chick-fil-A");
  std::vector<std::string> gt{
      "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920","6818427919",
      "6818427918","6818427892","6818427898","6818427917","6818427916","7232024780","6813416145",
      "6813416154","6813416153","6813416152","6813416151","6813416155","6808069740","6816193785",
      "6816193786","123152294","4015203136","4015203134","4015203133","21098539","6389467809",
      "4015203132","3195897587","4015203129","4015203127","6352865690","6813379589","6813379483",
      "3402887081","6814958394","3402887080","602606656","4872897515","4399697589","6814958391",
      "123209598","6787673296","122728406","6807762271","4399697304","4399697302","5231967015",
      "1862347583","3233702827","4540763379","6819179753","6820935900","6820935901","6813379556",
      "6820935898","1781230450","1781230449","4015405542","4015405543","1837212104","1837212107",
      "2753199985","6820935907","1837212100","4015372458","6813411588","1837212101","6814916516",
      "6814916515","6820935910","4547476733"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Bellman_Ford("Chick-fil-A", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Dijkstra
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford2) {
  TrojanMap m;
  
  auto path = m.CalculateShortestPath_Bellman_Ford("Target", "Chipotle");
  // Test from Target to Chipotle
  std::vector<std::string> gt{
      "5237417650","6814769289","6813379584","6813360961","6813379480","6813360960","6814620882","6813360954","6813360952","6813379420",
      "6813360951","6813360936","6813379467","6813379466","6813379465","6813379464","3402887075","6813379432","4536989637","4536989640",
      "3443310465","6813379491","6818390136","3433701978","4536989636","3432332948","6814770351","3431300454","4536993735","6814770342",
      "2776870272","5580882852","6814770345","2776870269","1472141961","5580883117","123153544","1673645147","2738332818","1673644724",
      "2738332817","122844997","5580881629","4399697303","4399697301","4399697300","6813379550","6814916523","1732243620","4015372469",
      "4015372463","6819179749","1732243544","6813405275","348121996","348121864","6813405280","1472141024","6813411590","216155217",
      "6820935908","9446678100","732641023"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Chipotle to Target
  path = m.CalculateShortestPath_Bellman_Ford("Chipotle", "Target");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Bellman_Ford
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford3) {
  TrojanMap m;
  
  auto path = m.CalculateShortestPath_Bellman_Ford("Popeyes", "Target");
  // Test from Popeyes to Target
  std::vector<std::string> gt{
    "5695236164","4835551075","3403035506","5680945537","6814916550","3398621871","6813565323","3403035498","6816193705","5556118325",
    "5680945525","7693467754","3403035499","3403035500","7863689394","7863689395","4835551084","2613117900","3403034586","4835551093",
    "2613117862","3403034590","2613117890","2613117915","4835551105","6813565334","2613117867","6787803635","6807905595","6813379406",
    "2613117879","3398578893","3398574892","6813565290","3398578898","6813379398","6813379505","6813379519","4399698005","3398578900",
    "4399698015","6813379425","3398578901","6813379479","6813379584","6814769289","5237417650"
  }; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Popeyes
  path = m.CalculateShortestPath_Bellman_Ford("Target", "Popeyes");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test Q7 cycle detection function
TEST(TrojanMapTest, CycleDetection) {
  TrojanMap m;
  
  // Test case 1 
  std::vector<double> square1 = {-118.299, -118.264, 34.032, 34.011};
  auto sub1 = m.GetSubgraph(square1);
  bool result1 = m.CycleDetection(sub1, square1);
  EXPECT_EQ(result1, true);

  // Test case 2 
  std::vector<double> square2 = {-118.290, -118.289, 34.030, 34.020};
  auto sub2 = m.GetSubgraph(square2);
  bool result2 = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result2, false);
}


TEST(TrojanMapTest, CycleDetection2) {
  TrojanMap m;
  
  // Test case 1 
  std::vector<double> square1 = {-118.2991, -118.2641, 34.0321, 34.0111};
  auto sub1 = m.GetSubgraph(square1);
  bool result1 = m.CycleDetection(sub1, square1);
  EXPECT_EQ(result1, true);

  // Test case 2 
  std::vector<double> square2 = {-118.2901, -118.2891, 34.0301, 34.0201};
  auto sub2 = m.GetSubgraph(square2);
  bool result2 = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result2, false);
}

TEST(TrojanMapTest, TopologicalSort1) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
  std::vector<std::vector<std::string>> dependencies = {{"Cardinal Gardens","Coffee Bean1"}, {"Cardinal Gardens","CVS"}, {"Coffee Bean1","CVS"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Cardinal Gardens", "Coffee Bean1","CVS"};
  EXPECT_EQ(result, gt);
}

TEST(TrojanMapTest, TopologicalSort2) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS", "Target", "Ralphs"};
  std::vector<std::vector<std::string>> dependencies = {{"Cardinal Gardens","Coffee Bean1"}, {"Cardinal Gardens","CVS"}, {"Coffee Bean1","CVS"}, {"Target","Ralphs"}, {"Target","CVS"}, {"CVS","Ralphs"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  for (auto& x: result)
    std::cout << x << std::endl;
  for (auto& d: dependencies) {
    auto it1 = find (result.begin(), result.end(), d[0]);
    auto it2 = find (result.begin(), result.end(), d[1]);
    EXPECT_EQ(it1 < it2, true);
  }
}