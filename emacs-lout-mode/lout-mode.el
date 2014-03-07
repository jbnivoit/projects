;; lout.el --- major mode for editing Lout files

;; Copyright (C) 1999 Free Software Foundation, Inc.

;; Author: Jean-Baptiste Nivoit
;; Maintainer: jbn@multimania.com
;; Created:    adapted from cc-mode.el
;; Keywords:   lout document formatting languages

;;
;; Works ok with FSF Emacs 20.2
;; & XEmacs 20.3
;;

;;
;; This version mainly has some syntax highlighting support.
;; Tested with the setup files provided with lout & some of my own.
;; This should work equally well with setup files and documents.
;;

;;
;; Still to todo: add support for indentation.
;; Problem highlighting when using tags with no '@' at the beginning.
;; Problem highlighting when using a language keyword as a tag.
;; Speed can probably be improved (suggestions welcome) (try it on 'dl', and you'll see what i'm talking about).
;;

(defconst lout-version "0.01" "Lout mode version number")

(require 'font-lock)

(defconst lout-font-lock-keywords 
  (purecopy
   (list
    ;;'("/\\([A-Z0-9_]+\\)[ \t]+{" 1 'font-lock-function-name-face)
    '("\\(#.*\\)" 1 'font-lock-comment-face) 
    
    ;; the following were extracted from the file 'externs' in the lout 3.08 distribution.
    '("\\(hyphen\\|nohyphen\\|adjust\\|outdent\\|ragged\\|cragged\\|rragged\\|lines\\|clines\\|rlines\\)[ \t\n\r}]" 1 'font-lock-keyword-face)
    '("\\(lout\\|compress\\|separate\\|troff\\|tex\\)[ \t\n\r}]" 1 'font-lock-keyword-face)
    '("\\(smallcaps\\|nosmallcaps\\)[ \t\n\r}]" 1 'font-lock-keyword-face)
    '("[ \t\n\r\f]\\(\\\\Start\\|\\\\Print\\|def\\|fontdef\\|langdef\\|force\\|horizontally\\|into\\|extend\\|import\\|export\\|associativity\\|left\\|right\\|body\\|macro\\|named\\)[ \t\n\r\f]" 1 'font-lock-keyword-face)
    '("\\(precedence[ \t\n\r\f]+[0-9]+\\)" 1 'font-lock-keyword-face) ; a separate regexp to highlight the precedence value as well
    '("\\(@\\(OptGall\\|Filter\\|FilterIn\\|FilterOut\\|FilterErr\\|Common\\|Rump\\|Insert\\|Next\\|Wide\\|High\\|HShift\\|VShift\\|OneCol\\|OneRow\\|HScale\\|VScale\\|HCover\\|VCover\\|Scale\\|HContract\\|VContract\\|HExpand\\|VExpand\\|PAdjust\\|HAdjust\\|VAdjust\\|Rotate\\|IncludeGraphic\\|SysIncludeGraphic\\|Graphic\\|Case\\|Yield\\|BackEnd\\|Char\\|Font\\|Space\\|YUnit\\|ZUnit\\|Break\\|Underline\\|SetColour\\|SetColor\\|Language\\|CurrLang\\|LEnv\\|LClos\\|LVis\\|LUse\\|Open\\|Use\\|NotRevealed\\|Tagged\\|Database\\|SysDatabase\\|Include\\|SysInclude\\|PrependGraphic\\|SysPrependGraphic\\|Target\\)\\)[ \t\n\r\\f]" 1 'font-lock-keyword-face)
    '("\\(following\\|preceding\\|foll_or_prec\\|now\\)" 1 'font-lock-keyword-face)
    
    ;; we can even do the first character discrimination for the regexp builder.
    '("\\(@\\(Null\\|PageLabel\\|Galley\\|ForceGalley\\|LInput\\|Split\\|Tag\\|Key\\|Optimize\\|Merge\\|Begin\\|End\\)\\)[ \t\n\r\f]" 1 'font-lock-keyword-face)

    '("\\(\\(//\\|&&\\|^//\\|/\\|^/\\|||\\|^||\\||\\|^|\\|&\\|^&\\)\\(\\([0-9]+\\(\\.[0-9]*\\)?\\|\\.[0-9]+\\)[fvxbiprtcoe]*\\)?\\)" 1 'font-lock-type-face)

    '("\\(@\\(Moment\\|Second\\|Minute\\|Hour\\|Day\\|Month\\|Year\\|Century\\|WeekDay\\|YearDay\\|DaylightSaving\\)\\)[ \t\n\r\f]" 1 'font-lock-function-name-face)
    '("\\(@[_A-z]+\\)[ \t\n\r{&.]" 1 'font-lock-variable-name-face)
    '("\\([{}]\\)" 1 'font-lock-reference-face)
    )
   )
  "The list of keywords that we want highlighted by font-lock...")

(put 'lout-mode 'font-lock-defaults '(lout-font-lock-keywords))

(defun lout-mode ()
  "Major mode for editing lout code."
  (interactive)
  (kill-all-local-variables)
  (setq major-mode 'lout-mode 
	mode-name "Lout"
	font-lock-defaults '(lout-font-lock-keywords))
  (make-local-variable 'font-lock-defaults)
  (run-hooks 'lout-mode-hook)
  )

(provide 'lout-mode)

