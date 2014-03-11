
WCHAR *A2COLE(char *in) {
	WCHAR *out = (WCHAR*)malloc(sizeof(WCHAR)*strlen(in));
	swprintf(out,L"%hs",in);

	return out;
}

class MyCComVariant : public tagVARIANT
{
// Constructors
public:
	MyCComVariant() throw()
	{
		::VariantInit(this);
	}
	~MyCComVariant() throw()
	{
		Clear();
	}

	MyCComVariant(const VARIANT& varSrc)
	{
		vt = VT_EMPTY;
		InternalKopy(&varSrc);
	}

	MyCComVariant(const MyCComVariant& varSrc)
	{
		vt = VT_EMPTY;
		InternalKopy(&varSrc);
	}
	MyCComVariant(LPCOLESTR lpszSrc)
	{
		vt = VT_EMPTY;
		*this = lpszSrc;
	}

	MyCComVariant(LPCSTR lpszSrc)
	{
		vt = VT_EMPTY;
		*this = lpszSrc;
	}

	MyCComVariant(bool bSrc)
	{
		vt = VT_BOOL;
		boolVal = bSrc;
	}

	MyCComVariant(int nSrc, VARTYPE vtSrc = VT_I4) throw()
	{

		vt = vtSrc;
		intVal = nSrc;
	}
	MyCComVariant(BYTE nSrc) throw()
	{
		vt = VT_UI1;
		bVal = nSrc;
	}
	MyCComVariant(short nSrc) throw()
	{
		vt = VT_I2;
		iVal = nSrc;
	}
	MyCComVariant(long nSrc, VARTYPE vtSrc = VT_I4) throw()
	{

		vt = vtSrc;
		lVal = nSrc;
	}
	MyCComVariant(float fltSrc) throw()
	{
		vt = VT_R4;
		fltVal = fltSrc;
	}
	MyCComVariant(double dblSrc, VARTYPE vtSrc = VT_R8) throw()
	{

		vt = vtSrc;
		dblVal = dblSrc;
	}
	MyCComVariant(LONGLONG nSrc) throw()
	{
		vt = VT_I8;
		llVal = nSrc;
	}
	MyCComVariant(ULONGLONG nSrc) throw()
	{
		vt = VT_UI8;
		ullVal = nSrc;
	}
	MyCComVariant(CY cySrc) throw()
	{
		vt = VT_CY;
		cyVal.Hi = cySrc.Hi;
		cyVal.Lo = cySrc.Lo;
	}
	MyCComVariant(IDispatch* pSrc) throw()
	{
		vt = VT_DISPATCH;
		pdispVal = pSrc;
		// Need to AddRef as VariantClear will Release
		if (pdispVal != NULL)
			pdispVal->AddRef();
	}
	MyCComVariant(IUnknown* pSrc) throw()
	{
		vt = VT_UNKNOWN;
		punkVal = pSrc;
		// Need to AddRef as VariantClear will Release
		if (punkVal != NULL)
			punkVal->AddRef();
	}
	MyCComVariant(unsigned short nSrc) throw()
	{
		vt = VT_UI2;
		uiVal = nSrc;
	}
	MyCComVariant(unsigned long nSrc) throw()
	{
		vt = VT_UI4;
		ulVal = nSrc;
	}
	MyCComVariant(unsigned int nSrc, VARTYPE vtSrc = VT_UI4) throw()
	{

		vt = vtSrc;
		uintVal= nSrc;
	}
	MyCComVariant(const SAFEARRAY *pSrc)
	{
		LPSAFEARRAY pKopy;
		if (pSrc != NULL)
		{
			HRESULT hRes = ::SafeArrayCopy((LPSAFEARRAY)pSrc, &pKopy);
			if (SUCCEEDED(hRes) && pKopy != NULL)
			{
				::SafeArrayGetVartype((LPSAFEARRAY)pSrc, &vt);
				vt |= VT_ARRAY;
				parray = pKopy;
			}
			else
			{
				vt = VT_ERROR;
				scode = hRes;
			}
		}
	}
// Assignment Operators
public:
	MyCComVariant& operator=(const MyCComVariant& varSrc)
	{
		InternalKopy(&varSrc);
		return *this;
	}
	MyCComVariant& operator=(const VARIANT& varSrc)
	{
		InternalKopy(&varSrc);
		return *this;
	}
	MyCComVariant& operator=(bool bSrc)
	{
		if (vt != VT_BOOL)
		{
			Clear();
			vt = VT_BOOL;
		}
		boolVal = bSrc;
		return *this;
	}

	MyCComVariant& operator=(BYTE nSrc) throw()
	{
		if (vt != VT_UI1)
		{
			Clear();
			vt = VT_UI1;
		}
		bVal = nSrc;
		return *this;
	}

	MyCComVariant& operator=(short nSrc) throw()
	{
		if (vt != VT_I2)
		{
			Clear();
			vt = VT_I2;
		}
		iVal = nSrc;
		return *this;
	}

	MyCComVariant& operator=(long nSrc) throw()
	{
		if (vt != VT_I4)
		{
			Clear();
			vt = VT_I4;
		}
		lVal = nSrc;
		return *this;
	}

	MyCComVariant& operator=(float fltSrc) throw()
	{
		if (vt != VT_R4)
		{
			Clear();
			vt = VT_R4;
		}
		fltVal = fltSrc;
		return *this;
	}

	MyCComVariant& operator=(double dblSrc) throw()
	{
		if (vt != VT_R8)
		{
			Clear();
			vt = VT_R8;
		}
		dblVal = dblSrc;
		return *this;
	}

	MyCComVariant& operator=(CY cySrc) throw()
	{
		if (vt != VT_CY)
		{
			Clear();
			vt = VT_CY;
		}
		cyVal.Hi = cySrc.Hi;
		cyVal.Lo = cySrc.Lo;
		return *this;
	}

	MyCComVariant& operator=(IDispatch* pSrc) throw()
	{
		Clear();
		vt = VT_DISPATCH;
		pdispVal = pSrc;
		// Need to AddRef as VariantClear will Release
		if (pdispVal != NULL)
			pdispVal->AddRef();
		return *this;
	}

	MyCComVariant& operator=(IUnknown* pSrc) throw()
	{
		Clear();
		vt = VT_UNKNOWN;
		punkVal = pSrc;

		// Need to AddRef as VariantClear will Release
		if (punkVal != NULL)
			punkVal->AddRef();
		return *this;
	}

	MyCComVariant& operator=(unsigned short nSrc) throw()
	{
		if (vt != VT_UI2)
		{
			Clear();
			vt = VT_UI2;
		}
		uiVal = nSrc;
		return *this;
	}

	MyCComVariant& operator=(unsigned long nSrc) throw()
	{
		if (vt != VT_UI4)
		{
			Clear();
			vt = VT_UI4;
		}
		ulVal = nSrc;
		return *this;
	}

	MyCComVariant& operator=(unsigned int nSrc) throw()
	{
		if (vt != VT_UI4)
		{
			Clear();
			vt = VT_UI4;
		}
		uintVal= nSrc;
		return *this;
	}

	MyCComVariant& operator=(LONGLONG nSrc) throw()
	{
		if (vt != VT_I8)
		{
			Clear();
			vt = VT_I8;
		}
		llVal = nSrc;

		return *this;
	}

	MyCComVariant& operator=(ULONGLONG nSrc) throw()
	{
		if (vt != VT_UI8)
		{
			Clear();
			vt = VT_UI8;
		}
		ullVal = nSrc;

		return *this;
	}

	MyCComVariant& operator=(const SAFEARRAY *pSrc)
	{
		Clear();
		LPSAFEARRAY pKopy;
		if (pSrc != NULL)
		{
			HRESULT hRes = ::SafeArrayCopy((LPSAFEARRAY)pSrc, &pKopy);
			if (SUCCEEDED(hRes) && pKopy != NULL)
			{
				::SafeArrayGetVartype((LPSAFEARRAY)pSrc, &vt);
				vt |= VT_ARRAY;
				parray = pKopy;
			}
			else
			{
				vt = VT_ERROR;
				scode = hRes;
			}
		}
		return *this;
	}

// Comparison Operators
public:
	bool operator==(const VARIANT& varSrc) const throw()
	{
		// For backwards compatibility
		if (vt == VT_NULL && varSrc.vt == VT_NULL)
			return true;
		return VarCmp((VARIANT*)this, (VARIANT*)&varSrc, LOCALE_USER_DEFAULT, 0) == VARCMP_EQ;
	}

	bool operator!=(const VARIANT& varSrc) const throw()
	{
		return !operator==(varSrc);
	}
	
	bool operator<(const VARIANT& varSrc) const throw()
	{
		if (vt == VT_NULL && varSrc.vt == VT_NULL)
			return false;
		return VarCmp((VARIANT*)this, (VARIANT*)&varSrc, LOCALE_USER_DEFAULT, 0)==VARCMP_LT;
	}

	bool operator>(const VARIANT& varSrc) const throw()
	{
		if (vt == VT_NULL && varSrc.vt == VT_NULL)
			return false;
		return VarCmp((VARIANT*)this, (VARIANT*)&varSrc, LOCALE_USER_DEFAULT, 0)==VARCMP_GT;
	}

// Operations
public:
	HRESULT Clear() { return ::VariantClear(this); }
	HRESULT Kopy(const VARIANT* pSrc) { return ::VariantCopy(this, const_cast<VARIANT*>(pSrc)); }
	// copy VARIANT to BSTR
	HRESULT KopyTo(BSTR *pstrDest)
	{

		HRESULT hRes = E_POINTER;
		if (pstrDest != NULL && vt == VT_BSTR)
		{
			*pstrDest = ::SysAllocStringByteLen((char*)bstrVal, ::SysStringByteLen(bstrVal));
			if (*pstrDest == NULL)
				hRes = E_OUTOFMEMORY;
			else
				hRes = S_OK;
		}
		else if (vt != VT_BSTR)
			hRes = DISP_E_TYPEMISMATCH;
		return hRes;
	}
	HRESULT Attach(VARIANT* pSrc)
	{
		// Clear out the variant
		HRESULT hr = Clear();
		if (!FAILED(hr))
		{
			// Kopy the contents and give control to MyCComVariant
			memcpy(this, pSrc, sizeof(VARIANT));
			pSrc->vt = VT_EMPTY;
			hr = S_OK;
		}
		return hr;
	}

	HRESULT Detach(VARIANT* pDest)
	{

		// Clear out the variant
		HRESULT hr = ::VariantClear(pDest);
		if (!FAILED(hr))
		{
			// Kopy the contents and remove control from MyCComVariant
			memcpy(pDest, this, sizeof(VARIANT));
			vt = VT_EMPTY;
			hr = S_OK;
		}
		return hr;
	}

	HRESULT ChangeType(VARTYPE vtNew, const VARIANT* pSrc = NULL)
	{
		VARIANT* pVar = const_cast<VARIANT*>(pSrc);
		// Convert in place if pSrc is NULL
		if (pVar == NULL)
			pVar = this;
		// Do nothing if doing in place convert and vts not different
		return ::VariantChangeType(this, pVar, 0, vtNew);
	}

	// Return the size in bytes of the current contents
	ULONG GetSize() const;

// Implementation
public:
	HRESULT InternalClear()
	{
		HRESULT hr = Clear();

		if (FAILED(hr))
		{
			vt = VT_ERROR;
			scode = hr;
		}
		return hr;
	}

	void InternalKopy(const VARIANT* pSrc)
	{
		HRESULT hr = Kopy(pSrc);
		if (FAILED(hr))
		{
			vt = VT_ERROR;
			scode = hr;
		}
	}
};


inline ULONG MyCComVariant::GetSize() const
{
	ULONG nSize = sizeof(VARTYPE);
	HRESULT hr;

	switch (vt)
	{
	case VT_UNKNOWN:
	case VT_DISPATCH:
		break;
	case VT_UI1:
	case VT_I1:
		nSize += sizeof(BYTE);
		break;
	case VT_I2:
	case VT_UI2:
	case VT_BOOL:
		nSize += sizeof(short);
		break;
	case VT_I4:
	case VT_UI4:
	case VT_R4:
	case VT_INT:
	case VT_UINT:
	case VT_ERROR:
		nSize += sizeof(long);
		break;
	case VT_R8:
	case VT_CY:
	case VT_DATE:
		nSize += sizeof(double);
		break;
	default:
		break;
	}
	if (nSize == sizeof(VARTYPE))
	{
		BSTR        bstr = NULL;
		MyCComVariant varBSTR;
		if (vt != VT_BSTR)
		{
			hr = VariantChangeType(&varBSTR, const_cast<VARIANT*>((const VARIANT*)this), VARIANT_NOVALUEPROP, VT_BSTR);
			if (SUCCEEDED(hr))
				bstr = varBSTR.bstrVal;
		}
		else
			bstr = bstrVal;
			
		// Add the size of the length, the string itself and the NULL character
		if (bstr != NULL)
			nSize += sizeof(ULONG) + SysStringByteLen(bstr) + sizeof(OLECHAR);
	}
	return nSize;
}
