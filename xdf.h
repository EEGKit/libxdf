#ifndef XDF_H
#define XDF_H

#include <string>
#include <vector>


class Xdf
{

public:
    Xdf();

    struct Stream
    {
        std::vector<std::vector<float> > time_series;
        std::vector<float> time_stamps;

        struct
        {
            std::string name;
            std::string type;
            int channel_count;
            double nominal_srate;
            std::string channel_format;
            std::string source_id;
            float version;
            double created_at;
            std::string uid;
            std::string session_id;
            std::string hostname;
            std::string v4address;
            int v4data_port;
            int v4service_port;
            std::string v6address;
            int v6data_port;
            int v6service_port;
            std::string desc;
            std::vector<std::pair<double, double> > clock_offsets;
            double first_timestamp;
            double last_timestamp;
            int sample_count;
            double measured_srate;
            //std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > desc;
        } info;

        struct
        {
            int num_samples;
            double t_begin;
            double t_end;
            double duration;
            double effective_srate;
        } segment;

        float last_timestamp{ 0 };  //for temporary use
        float sampling_interval;    //if srate>0,sampling_interval=1/srate;otherwise 0
        std::vector<double> clock_times;
        std::vector<double> clock_values;
    };


    struct XDFdataStruct	//final return value
    {
        std::vector<Stream> streams;
        struct
        {
            struct
            {
                float version;
            }info;
        } fileHeader;

        uint64_t totalLen;
        float minTS {0};
        float maxTS {0};
        int totalCh {0};
        int majSR;      //the sample rate that has the most channels;
        std::vector<std::pair<int, unsigned> > streamMap; //streamNum, channel count

        typedef std::string eventName;
        typedef float eventTimeStamp;

        std::vector<std::pair<eventName, eventTimeStamp> > eventMap; //copy all the events of all streams to here <events, timestamps>
    };

    void load_xdf(XDFdataStruct &XDFdata, std::string filename);

    uint64_t readLength(std::ifstream &file);

};

#endif // XDF_H