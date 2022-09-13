using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace EDCHOST24
{
    // STL : Storage the Package
    public class PackageList //存储预备要用的物资信息
    {
        private static List<Package> mPackageList;

        private int X_MAX;
        private int X_MIN;
        private int Y_MAX;
        private int Y_MIN;
        private int LIMITED_TIME;
        private int TIME_INTERVAL;

        // point to the next generated package 
        public int mPointer;

        public PackageList(int _X_MAX, int _X_MIN, int _Y_MAX, int _Y_MIN, int _INITIAL_AMOUNT, int _LIMITED_TIME, int _TIME_INTERVAL) //生成指定数量的物资
        {
            mPointer = _INITIAL_AMOUNT;

            X_MAX = _X_MAX;
            X_MIN = _X_MIN;
            Y_MAX = _Y_MAX;
            Y_MIN = _Y_MIN;
            LIMITED_TIME = _LIMITED_TIME;
            TIME_INTERVAL = _TIME_INTERVAL;

            mPackageList = new List<Package>();
            Random NRand = new Random();

            // initialize package at the beginning of game
            for (int i = 0; i < _INITIAL_AMOUNT; i++)
            {
                Dot Departure = new Dot(NRand.Next(X_MIN, X_MAX), NRand.Next(Y_MIN, Y_MAX));
                Dot Destination = new Dot(NRand.Next(X_MIN, X_MAX), NRand.Next(Y_MIN, Y_MAX));

                if (!(Dot.IsPosLegal(Departure) && Dot.IsPosLegal(Destination)))
                {
                    i--;
                    continue;
                }

                mPackageList.Add(new Package(Departure, Destination, 0));
            }


            // generate the time series for packages
            int LastGenerationTime = 0;
            for (int i = _INITIAL_AMOUNT; LastGenerationTime + TIME_INTERVAL <= LIMITED_TIME; i++)
            {
                Dot Departure = new Dot(NRand.Next(X_MIN, X_MAX), NRand.Next(Y_MIN, Y_MAX));
                Dot Destination = new Dot(NRand.Next(X_MIN, X_MAX), NRand.Next(Y_MIN, Y_MAX));

                if (!(Dot.IsPosLegal(Departure) && Dot.IsPosLegal(Destination)))
                {
                    i--;
                    continue;
                }

                int GenerationTime = NRand.Next(LastGenerationTime, LastGenerationTime + TIME_INTERVAL);

                LastGenerationTime = GenerationTime;
                mPackageList.Add(new Package(Departure, Destination, 0));
            }
        }


        public Package Index(int i)
        {
            return mPackageList[i];
        }

        public int Amount()
        {
            return mPackageList.Count();
        }

        public Package GeneratePackage()
        {
            mPointer++;
            return mPackageList[mPointer - 1];
        }

        public int NextGenerationTime()
        {
            return mPackageList[mPointer].GenerationTime();
        }

        public void ResetPointer()
        {
            mPointer = 0;
        }

        // 检查所有package，整个检测程序写在Dot里
        public static bool IsPackageExisted(Dot adot)
        {
            //check mPackageList
            foreach(Package element in mPackageList)
            {
                if(element.IsDotExisted(adot))
                {
                    return true;
                }
            }
            return false;
        }

    }
}