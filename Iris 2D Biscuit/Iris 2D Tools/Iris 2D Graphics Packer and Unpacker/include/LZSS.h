// LZSS.h: interface for the CLZSS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LZSS_H__F713E48C_2DB4_4FA2_B8E6_1B0226A9F215__INCLUDED_)
#define AFX_LZSS_H__F713E48C_2DB4_4FA2_B8E6_1B0226A9F215__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <Windows.h>

#define N		 4096	/* size of ring buffer */
#define F		   18	/* upper limit for match_length */
#define THRESHOLD	2   /* encode string into position and length
						   if match_length is greater than this */
#define NIL			N	/* index for root of binary search trees */

typedef unsigned long DWORD;
typedef unsigned char BYTE;

class CLZSS  
{
public:
	CLZSS();
	virtual ~CLZSS();

public:
	void Encode(const char *infile, const char *outfile);
	void Decode(const char *infile, const char *outfile);

	void EncodeData(const char* pOrgData, char** pSrcData, DWORD nOrgDataSize, DWORD* pnSrcDataSize);
	void DecodeData(const char* pSrcData, char** pDestData, DWORD nSrcDataSize, DWORD nOrgDestDataSize);

private:
	unsigned char text_buf[N + F - 1];	/*	ring buffer of size N,
											with extra F-1 bytes to facilitate string comparison */
	int match_position, match_length,	/*	of longest match.  These are
											set by the InsertNode() procedure. */
		lson[N + 1], rson[N + 257], dad[N + 1];
										/* left & right children & parents
											-- These constitute binary search trees. */
private:
	void InitTree(void);		/* initialize trees */
	void InsertNode(int r);
	void DeleteNode(int p);		/* deletes node p from tree */
	void Encode(FILE *infile, FILE *outfile);
	void Decode(FILE *infile, FILE *outfile);			/* Just the reverse of Encode(). */
};

#endif // !defined(AFX_LZSS_H__F713E48C_2DB4_4FA2_B8E6_1B0226A9F215__INCLUDED_)
