#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

// Test Autocomplete function:
TEST(TrojanMapTest, Autocomplete1) {
  TrojanMap m;
  
  // Test the simple case
  auto names = m.Autocomplete("Ch");
  std::unordered_set<std::string> gt1 = {"Chinese Street Food", "Chase", "Chevron 2", "Chucks Chicken & Waffles", "Cheebos Burger", "Chick-fil-A",
  "Chevron 1", "Church of Christ", "Chipotle", "Chase Plaza Heliport", "Chevron"}; // groundtruth for "Ch"
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt1.count(n) > 0, true);
    if (gt1.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt1.size());
  // Test the lower case 
  names = m.Autocomplete("ch");
  std::unordered_set<std::string> gt2 = {"Chinese Street Food", "Chase", "Chevron 2", "Chucks Chicken & Waffles", "Cheebos Burger", "Chick-fil-A",
  "Chevron 1", "Church of Christ", "Chipotle", "Chase Plaza Heliport", "Chevron"}; // groundtruth for "ch"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt2.count(n) > 0, true);
    if (gt2.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt2.size());
  // Test the lower and upper case
  names = m.Autocomplete("cH"); 
  std::unordered_set<std::string> gt3 = {"Chinese Street Food", "Chase", "Chevron 2", "Chucks Chicken & Waffles", "Cheebos Burger", "Chick-fil-A",
  "Chevron 1", "Church of Christ", "Chipotle", "Chase Plaza Heliport", "Chevron"}; // groundtruth for "cH"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt3.count(n) > 0, true);
    if (gt3.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt3.size());
  // Test the upper case
  names = m.Autocomplete("CH"); 
  std::unordered_set<std::string> gt4 = {"Chinese Street Food", "Chase", "Chevron 2", "Chucks Chicken & Waffles", "Cheebos Burger", "Chick-fil-A",
  "Chevron 1", "Church of Christ", "Chipotle", "Chase Plaza Heliport", "Chevron"}; // groundtruth for "cH"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt4.count(n) > 0, true);
    if (gt4.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt4.size());
}

TEST(TrojanMapTest, Autocomplete2) {
  TrojanMap m;
  
  // Test the simple case
  auto names = m.Autocomplete("Ra");
  std::unordered_set<std::string> gt1 = {"Ralphs", "Ramen KenJo"};
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt1.count(n) > 0, true);
    if (gt1.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt1.size());
  // Test the lower case
  names = m.Autocomplete("rA");
  std::unordered_set<std::string> gt2 = {"Ralphs", "Ramen KenJo"}; // groundtruth for "ch"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt2.count(n) > 0, true);
    if (gt2.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt2.size());

}

// Test FindPosition function
TEST(TrojanMapTest, FindPosition) {
  TrojanMap m;
  
  // Test Chick-fil-A
  auto position = m.GetPosition("Chick-fil-A");
  std::pair<double, double> gt1(34.0167334, -118.2825307); // groundtruth for "Chick-fil-A"
  EXPECT_EQ(position, gt1);
  // Test Ralphs
  position = m.GetPosition("Ralphs");
  std::pair<double, double> gt2(34.0317653, -118.2908339); // groundtruth for "Ralphs"
  EXPECT_EQ(position, gt2);
  // Test Target 
  position = m.GetPosition("Target");
  std::pair<double, double> gt3(34.0257016, -118.2843512); // groundtruth for "Target"
  EXPECT_EQ(position, gt3);
  // Test Unknown 
  position = m.GetPosition("XXX");
  std::pair<double, double> gt4(-1, -1);
  EXPECT_EQ(position, gt4);
  // Test KFC 
  position = m.GetPosition("Porterhouse Fried Chicken");
  std::pair<double, double> gt5(34.0038438, -118.3178156); // groundtruth for "KFC"
  EXPECT_EQ(position, gt5);
  // Test USC Village Dining Hall
  position = m.GetPosition("USC Parking");
  std::pair<double, double> gt6(34.0238824,-118.2801114); // groundtruth for "USC Village Dining Hall"
  EXPECT_EQ(position, gt6);
  // Test USC Village Gym 
  position = m.GetPosition("USC Village Gym");
  std::pair<double, double> gt7(34.0252392, -118.2858186); // groundtruth for "USC Village Gym"
  EXPECT_EQ(position, gt7);

}