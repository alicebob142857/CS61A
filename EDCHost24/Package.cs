using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//using EDCHOST24.Dot; 不需要

namespace EDCHOST24
{
    //Package
    public class Package
    {
        public const int ARRIVE_EASY_CREDIT = 20;   // scores for different levels of packages
        public const int ARRIVE_NORMAL_CREDIT = 25;
        public const int ARRIVE_HARD_CREDIT = 30;

        private Dot mDeparture;     // Departure of Package
        private Dot mDestination;   // Destination of Package

        // features added by EDA Host 24
        // author : Alfred Dai
        // all times are in ms
        private int mGenerationTime;
        private int mScheduledDeliveryTime;

        private int mPackageLevel;  //judge the package is easy/normal/hard to be arrived //0-easy; 1-normal; 2-hard;

        private int mScheduledScore;

        public Package(Dot inDeparturePos, Dot inDestinationPos, int inGenerationTime)
        {
            mDeparture = inDeparturePos;
            mDestination = inDestinationPos;
            mGenerationTime = inGenerationTime;
            mScheduledDeliveryTime = 20 * Dot.Distance(mDeparture, mDestination) + 1000;

            //judge level
            if (mDeparture.x >= 40 && mDeparture.x <= 214 && mDeparture.y >= 40 && mDeparture.y <= 214
                && mDestination.x >= 40 && mDestination.x <= 214 && mDestination.y >= 40 && mDestination.y <= 214)
            {
                if (Dot.Distance(mDeparture, mDestination) <= 120)
                {
                    mPackageLevel = 0;
                }
                else
                {
                    mPackageLevel = 1;
                }
            }
            else
            {
                mPackageLevel = 2;
            }
            //judge score
            switch (mPackageLevel)
            {
                case 0: mScheduledScore = ARRIVE_EASY_CREDIT; break;
                case 1: mScheduledScore = ARRIVE_NORMAL_CREDIT; break;
                case 2: mScheduledScore = ARRIVE_HARD_CREDIT; break;
            }
        }

        public Dot Departure()
        {
            return mDeparture;
        }

        public Dot Destination()
        {
            return mDestination;
        }

        public int GenerationTime()
        {
            return mGenerationTime;
        }

        public int ScheduledDeliveryTime()
        {
            return mScheduledDeliveryTime;
        }

        public int Distance2Departure(Dot _CarPos)
        {
            return Dot.Distance(_CarPos, mDeparture);
        }

        public int Distance2Destination(Dot _CarPos)
        {
            return Dot.Distance(_CarPos, mDestination);
        }

        public int GetPackageScore(int _ArrivalTime)
        {
            int PackageScore = 0;

            return PackageScore;
        }

        public bool IsDotExisted(Dot NewPos)
        {
            return (NewPos==mDeparture)||(NewPos==mDestination);
        }

    }
}
