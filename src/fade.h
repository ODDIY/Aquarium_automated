#ifndef FADE_H
#define FADE_H
/* Copyright (C) 2018 Oliver Walter - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU license, which unfortunately won't be
 * written for another century.
 *
 * You should have received a copy of the GNU license with
 * this file. If not, please write to: , or visit :
 */





class Fader
{
    /*!
 * \brief faderfn Werte berechen
 * \param start Start des fade-in
 * \param end Ende des fade-in
 * \param val Wert am ende des Fade-in
 * \param offStart start des fade-off
 * \param offEnd ende des fade-off
 * \param offVal wert am ende des fade-off
 * \param time Aktuelle fade time
 * \return
 */
    static int fadefn(float start, float end, float val, float offStart, float offEnd, float offVal, int time) {


        //OFF
        if (time < start) {
            return 0;
        }

        //FADE IN
        if (time >= start && time <= end) {
            //(start, 0)
            //(end, val)

            float a = val / (end - start);
            float b = (start * val) / (end - start);

            return a * time - b;
        }

        //ON
        if (time > end && time < offStart) {
            return val;
        }

        if (offStart != -1 && offEnd != -1 && offVal != val) {

            //FADE OFF
            if (time >= offStart && time <= offEnd) {
                float a = (offVal - val) / (offEnd - offStart);
                // int b = ((offEnd*val) - (offStart*offVal)) / (offEnd-offStart);
                float b = val - (((offVal - val) / (offEnd - offStart)) * offStart);
                return a * time + b;
            }

            //OFF
            if (time > offEnd) {
                return offVal;
            }
        } else {
            if (time > end) {
                return val;
            }
        }

        return 0;
    }

public:

    Fader() {
        this->start =0;
        this->end = 0;
        this->val = 0;
        this->offStart = 0;
        this->offEnd = 0;
        this->offVal = 0;
    }

    Fader(float start, float end, float val, float offStart,float offEnd, float offVal) {
        this->start =start;
        this->end = end;
        this->val = val;
        this->offStart = offStart;
        this->offEnd = offEnd;
        this->offVal = offVal;
    }

    void set(float start, float end, float val, float offStart,float offEnd, float offVal) {
        this->start =start;
        this->end = end;
        this->val = val;
        this->offStart = offStart;
        this->offEnd = offEnd;
        this->offVal = offVal;
    }

    int fade(int time) {
        return fadefn(start,end,val,offStart,offEnd,offVal,time);

    }

    float start;
    float end;
    float val;
    float offStart;
    float offEnd;
    float offVal;
};






#endif // FADE_H
