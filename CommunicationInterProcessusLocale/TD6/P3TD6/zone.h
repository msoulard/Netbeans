/* 
 * File:   zone.h
 * Author: msoulard
 *
 * Created on 12 octobre 2020, 11:14
 */
#pragma pack(push, 1)
#ifndef ZONE_H
#define ZONE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    float temp; //4 octets
    int press; //4 octets
    char ordre; //1 octet
} structPartagee;


#ifdef __cplusplus
}
#endif

#endif /* ZONE_H */

