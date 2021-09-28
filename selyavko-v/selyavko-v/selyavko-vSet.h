
// selyavko-vSet.h: interface of the CselyavkovSet class
//


#pragma once

// code generated on понедельник, 27 сент€бр€ 2021 г., 21:16

class CselyavkovSetAccessor
{
public:
	int m_ID;
	char m_name[51];
	char m_place[51];
	char m_date[51];

	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!

	DBSTATUS m_dwIDStatus;
	DBSTATUS m_dwnameStatus;
	DBSTATUS m_dwplaceStatus;
	DBSTATUS m_dwdateStatus;

	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!

	DBLENGTH m_dwIDLength;
	DBLENGTH m_dwnameLength;
	DBLENGTH m_dwplaceLength;
	DBLENGTH m_dwdateLength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_IRowsetChange, true);
		pPropSet->AddProperty(DBPROP_IRowsetScroll, true);
		pPropSet->AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	}

	HRESULT OpenDataSource()
	{
		CDataSource _db;
		HRESULT hr;
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
		hr = _db.OpenFromInitializationString(L"Provider=MSDASQL.1;Persist Security Info=False;Data Source=lab5;Mode=ReadWrite;Extended Properties=\"DSN=lab5;UID=;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=DESKTOP-1OH4LVK;DATABASE=lab5\"");
		if (FAILED(hr))
		{
#ifdef _DEBUG
			AtlTraceErrorRecords(hr);
#endif
			return hr;
		}
		return m_session.Open(_db);
	}

	void CloseDataSource()
	{
		m_session.Close();
	}

	operator const CSession&()
	{
		return m_session;
	}

	CSession m_session;

	BEGIN_COLUMN_MAP(CselyavkovSetAccessor)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_ID, m_dwIDLength, m_dwIDStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_name, m_dwnameLength, m_dwnameStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_place, m_dwplaceLength, m_dwplaceStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_date, m_dwdateLength, m_dwdateStatus)
	END_COLUMN_MAP()



};

class CselyavkovSet : public CCommand<CAccessor<CselyavkovSetAccessor> >
{
public:
	HRESULT OpenAll()
	{
		HRESULT hr;
		hr = OpenDataSource();
		if (FAILED(hr))
			return hr;
		__if_exists(GetRowsetProperties)
		{
			CDBPropSet propset(DBPROPSET_ROWSET);
			__if_exists(HasBookmark)
			{
				if( HasBookmark() )
					propset.AddProperty(DBPROP_IRowsetLocate, true);
			}
			GetRowsetProperties(&propset);
			return OpenRowset(&propset);
		}
		__if_not_exists(GetRowsetProperties)
		{
			__if_exists(HasBookmark)
			{
				if( HasBookmark() )
				{
					CDBPropSet propset(DBPROPSET_ROWSET);
					propset.AddProperty(DBPROP_IRowsetLocate, true);
					return OpenRowset(&propset);
				}
			}
		}
		return OpenRowset();
	}

	HRESULT OpenRowset(DBPROPSET *pPropSet = NULL)
	{
		HRESULT hr = Open(m_session, L"select * from dbo.[user]", pPropSet);

#ifdef _DEBUG
		if(FAILED(hr))
			AtlTraceErrorRecords(hr);
#endif
		return hr;
	}

	void CloseAll()
	{
		Close();
		CloseDataSource();
	}
	HRESULT ReOpen(CString where_str = L"", CString order_str = L"")
	{
		CDBPropSet propset(DBPROPSET_ROWSET);
		propset.AddProperty(DBPROP_IRowsetLocate, true);
		GetRowsetProperties(&propset);
		CString select_str;
		if (where_str.IsEmpty())
			select_str.Format(L"select * from dbo.[user] order by %s", order_str);
		else
			select_str.Format(L"select * from dbo.[user]  where %s order by %s", where_str, order_str);
		Close();
		HRESULT hr = Open(m_session, select_str, &propset);
#ifdef _DEBUG
		if (FAILED(hr))
			AtlTraceErrorRecords(hr);
#endif
		return hr;
	}

};

