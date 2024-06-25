#pragma once

struct GDTEntry
{
	unsigned short limitLow;
	unsigned short baseLow;
	unsigned char baseMiddle;
	unsigned char access;
	unsigned char granularity;
	unsigned char baseHigh;
} __attribute__((packed));

struct GDTPointer
{
    unsigned short limit;
    unsigned long base;
} __attribute__((packed));

static void EncodeGDTEntry(GDTEntry* entry, unsigned long base, unsigned long limit, unsigned char access, unsigned char granularity);
void LoadGDT();