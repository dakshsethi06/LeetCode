class Solution:
    def earliestFinishTime(self, landStartTime, landDuration, waterStartTime, waterDuration):
        ans = float('inf')

        for i in range(len(landStartTime)):
            for j in range(len(waterStartTime)):
                # Land -> Water
                land_finish = landStartTime[i] + landDuration[i]
                water_start = max(land_finish, waterStartTime[j])
                finish1 = water_start + waterDuration[j]

                # Water -> Land
                water_finish = waterStartTime[j] + waterDuration[j]
                land_start = max(water_finish, landStartTime[i])
                finish2 = land_start + landDuration[i]

                ans = min(ans, finish1, finish2)

        return ans