/*********************************************************************

   Copyright (C) 1999 Smaller Animals Software, Inc.

   This software is provided 'as-is', without any express or implied
   warranty.  In no event will the authors be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.

   3. This notice may not be removed or altered from any source distribution.

   http://www.smalleranimals.com
   smallest@smalleranimals.com

**********************************************************************/

#include "stdafx.h"
#include "SAStatusLog.h"

/////////////////////////////////////////////////////////////////////////////

CSAStatusLog::CSAStatusLog()
{
	m_bEnable = FALSE;
   m_bPrintTime = FALSE;
	m_csFileName = _T("");

   m_csAppName = _T("");

   // we'll make sure only one call uses the critical stuff at a time
   InitializeCriticalSection(&m_crit);
}

/////////////////////////////////////////////////////////////////////////////

CSAStatusLog::~CSAStatusLog()
{
   DeleteCriticalSection(&m_crit);
}

/////////////////////////////////////////////////////////////////////////////

void CSAStatusLog::Init(const TCHAR *pOutputFilename)
{
	m_bEnable = TRUE;

   // get application path and name
	TCHAR buf[MAX_PATH+1];
	DWORD res = GetModuleFileName(AfxGetInstanceHandle(), buf, MAX_PATH);

	CString appDir = GetBaseDir(buf);

   m_csAppName = GetBaseName(buf);

   //m_csFileName.Format(_T("%s\\%s"), appDir, pOutputFilename);
	m_csFileName=pOutputFilename;
   // overwrite the old one!
	//_tremove(m_csFileName);
}

/////////////////////////////////////////////////////////////////////////////

void CSAStatusLog::Enable(BOOL bEnable)
{
	m_bEnable = bEnable;
}

/////////////////////////////////////////////////////////////////////////////

BOOL CSAStatusLog::StatusOut(const TCHAR* fmt, ...)
{
	if (m_csFileName.IsEmpty())
		return FALSE;

	if (!m_bEnable)
		return TRUE;

	if (!AfxIsValidString(fmt, -1))
		return FALSE;

   EnterCriticalSection(&m_crit);

   // parse that string format
   try
   {
	   va_list argptr;
	   va_start(argptr, fmt);
	   _vsntprintf(m_tBuf, TBUF_SIZE, fmt, argptr);
	   va_end(argptr);
   }
   catch (...)
   {
      m_tBuf[0] = 0;
   }

   BOOL bOK = FALSE;

   // output 
	FILE *fp = _tfopen(m_csFileName, _T("a"));
	if (fp)
	{
      if (m_bPrintAppName)
      {
         _ftprintf(fp,_T("%s : "), m_csAppName);
      }

      if (m_bPrintTime)
      {
		   CTime ct ; 
		   ct = CTime::GetCurrentTime();
		   _ftprintf(fp,_T("%s : "),ct.Format(_T("%m/%d/%Y %H:%M:%S")));
      }

      _ftprintf(fp, _T("%s\n"), m_tBuf);
		
      fclose(fp);

      bOK = TRUE;
	}

   LeaveCriticalSection(&m_crit);

	return bOK;
}

/////////////////////////////////////////////////////////////////////////////

CString	CSAStatusLog::GetBaseName(const CString &path)
{
	CString out = path;

	int iSlashPos = path.ReverseFind(_T('\\'));
	if (iSlashPos !=-1) 
	{
		out = out.Mid(iSlashPos+1);
	}
	else
	{
		iSlashPos = path.ReverseFind(_T('/'));
		if (iSlashPos !=-1) 
		{
			out = out.Mid(iSlashPos+1);
		}
	}

   int iDotPos = out.ReverseFind(_T('.'));
   if (iDotPos>0)
   {
      out = out.Left(iDotPos);
   }

	return out;
}

/////////////////////////////////////////////////////////////////////////////

CString CSAStatusLog::GetBaseDir(const CString & path)
{
	CString out = _T("");
	int iSlashPos = path.ReverseFind(_T('\\'));
	if (iSlashPos !=-1) 
	{
		out = path.Left(iSlashPos);
	} 
	else
	{
		iSlashPos = path.ReverseFind(_T('/'));
		if (iSlashPos !=-1) 
		{
			out = path.Left(iSlashPos);
		} 
	}

	return out;
}
