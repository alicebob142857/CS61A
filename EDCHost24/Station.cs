using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace EDCHOST24
{
    class Station //所有站点
    {
        private int MAX_STATION = 3;
        private List<Dot> mStationList1; //一个包含站点位置信息的list
        private List<Dot> mStationList2;
        public void Reset()
        {
            mStationList1.Clear();
            mStationList2.Clear();
        } //num复位
        public Station() //构造函数
        {
            List<Dot> mStationList1 = new List<Dot>();
            List<Dot> mStationList2 = new List<DateTimeOffset>();
        }

        private List<Dot> StationList(int _Type)
        {
            if (_Type == 0)
            {
                return mStationList1;
            }
            else
            {
                return mStationList2;
            }
        }
        public void Add(Dot _inPos, int _Type = 0)
        {
            List<Dot> mStationList = StationList(_Type);
            if (mStationList.Count() < MAX_STATION)
            {
                if (Dot.IsPosLegal(_inPos))
                {
                    mStationList.Add(_inPos);
                    Debug.WriteLine("New Station, ({0}, {1})", _inPos.x, _inPos.y);
                }
                else
                {
                    Debug.WriteLine("Failed! Location is illegal");
                }
            }
            else
            {
                Debug.WriteLine("Failed! Up to maximum");
            }
        }

        public static bool isCollided(Dot _CarPos, int _Type = 0, int r = 8 )
        {
            List<Dot> mStationList = StationList(_Type);
            foreach (Dot station in mStationList)
            {
                if (Dot.Distance(station, _CarPos) < r)
                {
                    return true;
                }
            }
            return false;
        }

        public Dot Index(int i, int _Type)
        {
            List<Dot> mStationList = StationList(_Type);
            if (i < mStationList.Count())
            {
                return mStationList[i];
            }
            return new Dot(-1, -1);
        }

        public List<Dot> StationOnStage(int _Type)
        {
            List<Dot> list = new List<Dot>();
            foreach (Dot dot in StationList(_Type))
            {
                list.Add(dot);
            }
            return list;
        }
    }

}