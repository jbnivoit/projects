;;; xmms.el --- specialized comint.el for running the xmms mp3 player through
;;; its Perl interface.

;; Copyright (C) 2000 Jean-Baptiste Nivoit

;; Author: Jean-Baptiste Nivoit <jbnivoit@multimania.com>
;; Maintainer: idem
;; Created: 04 Apr 2000
;; Keywords: mp3

;; This file is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2, or (at your option)
;; any later version.

;; This file is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with this file; see the file COPYING.  If not, write to the
;; Free Software Foundation, Inc., 59 Temple Place - Suite 330,
;; Boston, MA 02111-1307, USA.

;;
;; Most of the inspiration for this came from shell.el, cmuscheme.el and
;; tar-mode.el in the GNU Emacs 20.4 distribution.
;;
;; This mode communicates with Xmms using the Xmms::Perl Perl interface
;; i.e. it actually start a perl interpreter, load the Xmms extension into
;; it, and then feeds that process with commands; it doesn't talk directly to 
;; xmms (i always wondered what i'd be able to do with so much RAM, now i know ;-))
;;
;; Part of this package is meant to view .m3u files (really only a sequence of
;; file names which happen to be mp3 files), with support for interacting
;; with the 'xmms' player to play them.

;;
;; This file actually defines 2 modes:
;;    - 'inferior-xmms-mode' that interacts with the xmms process
;;    - 'xmms-playlist-mode' that manages the playlist. When you type 'enter' on
;;    a line in that buffer, it makes xmms play the corresponding file.
;;
;; When you use 'run-xmms', two buffers are opened, and you are presented
;; with the playlist buffer (the process buffer is not shown, because it's not
;; of much use except for advanced users that want & know how to send raw commands
;; to xmms).
;;

;;
;; TODO:
;;   - add support for all the commands (jtime?)
;;   - add support for a text mode interface that looks like xmms 
;;   - add support for playlist selection a la dired
;;   - for each file, we should have the ID3 tag displayed.
;;   - display the playlist in a menu as well, ordered properly
;;   - display associated comments
;;   - add support for mp3serverbox via telnet.
;;


(require 'comint)

(defgroup xmms nil
  "Run a xmms process in a buffer."
  :group 'processes
  :group 'unix)

;;; INFERIOR XMMS MODE STUFF
;;;============================================================================

(defcustom inferior-xmms-mode-hook nil
  "*Hook for customising inferior-xmms mode."
  :type 'hook
  :group 'xmms)

(defvar inferior-xmms-mode-map nil)

(cond ((not inferior-xmms-mode-map)
       (setq inferior-xmms-mode-map
	     (copy-keymap comint-mode-map))
       (define-key inferior-xmms-mode-map "\M-\C-x" ;gnu convention
	 'xmms-send-definition)
       (define-key inferior-xmms-mode-map "\C-x\C-e" 'xmms-send-last-sexp)
       (define-key inferior-xmms-mode-map "\C-c\C-l" 'xmms-load-file)
       (define-key inferior-xmms-mode-map "\C-c\C-k" 'xmms-compile-file)
       ;;(xmms-mode-commands inferior-xmms-mode-map)
       )) 

;; Install the process communication commands in the xmms-mode keymap.
;; Those are the same bindings as the bare 'Xmms::Perl'.
(define-key inferior-xmms-mode-map "\C-\-" 'xmms-volume-slide-up)
(define-key inferior-xmms-mode-map "\C-+"  'xmms-volume-slide-down)
(define-key inferior-xmms-mode-map "\M-="  'xmms-next)
(define-key inferior-xmms-mode-map "\M-\-" 'xmms-prev)
(define-key inferior-xmms-mode-map "\M-."  'xmms-stop)
(define-key inferior-xmms-mode-map "\M-/"  'xmms-play)
(define-key inferior-xmms-mode-map "\M-\\" 'xmms-jtime)
(define-key inferior-xmms-mode-map "\M-m"  'xmms-mtime)
(define-key inferior-xmms-mode-map "\M-,"  'xmms-pause)
(define-key inferior-xmms-mode-map "\M-~"  'xmms-shuffle)
(define-key inferior-xmms-mode-map "\M-@"  'xmms-repeat)
(define-key inferior-xmms-mode-map "\M-1"  'xmms-play-track-1)
(define-key inferior-xmms-mode-map "\M-2"  'xmms-play-track-2)
(define-key inferior-xmms-mode-map "\M-3"  'xmms-play-track-3)
(define-key inferior-xmms-mode-map "\M-4"  'xmms-play-track-4)
(define-key inferior-xmms-mode-map "\M-5"  'xmms-play-track-5)
(define-key inferior-xmms-mode-map "\M-6"  'xmms-play-track-6)
(define-key inferior-xmms-mode-map "\M-7"  'xmms-play-track-7)
(define-key inferior-xmms-mode-map "\M-8"  'xmms-play-track-8)
(define-key inferior-xmms-mode-map "\M-9"  'xmms-play-track-9)
(define-key inferior-xmms-mode-map "\M-a"  'xmms-show-all-windows)
(define-key inferior-xmms-mode-map "\M-w"  'xmms-main-window)
(define-key inferior-xmms-mode-map "\M-l"  'xmms-playlist-window)
(define-key inferior-xmms-mode-map "\M-q"  'xmms-equalizer-window)

(defvar xmms-mode-map nil "*Local keymap for xmms mode listings.")

(defvar xmms-parse-info nil) ;; this holds an array image of the playlist.
(defvar xmms-offset nil)

(put 'xmms-parse-info 'permanent-local t)

;; build the menu
(define-key inferior-xmms-mode-map [menu-bar xmms]
  (cons "Xmms" (make-sparse-keymap "Xmms")))
(define-key inferior-xmms-mode-map [menu-bar xmms play]           
  '("Play"          . xmms-play))
(define-key inferior-xmms-mode-map [menu-bar xmms next]           
  '("Next"          . xmms-next))
(define-key inferior-xmms-mode-map [menu-bar xmms previous] 
  '("Previous"      . xmms-prev))
(define-key inferior-xmms-mode-map [menu-bar xmms stop] 
  '("Stop"          . xmms-stop))
(define-key inferior-xmms-mode-map [menu-bar xmms pause]       
  '("Pause"         . xmms-pause))
(define-key inferior-xmms-mode-map [menu-bar xmms repeat]
  '("Repeat"        . xmms-repeat))
(define-key inferior-xmms-mode-map [menu-bar xmms shuffle]       
  '("Shuffle"       . xmms-shuffle))

;; copied from tar-mode.el
(defmacro xmms-dolist (control &rest body)
  "syntax: (dolist (var-name list-expr &optional return-value) &body body)"
  (let ((var (car control))
	(init (car (cdr control)))
	(val (car (cdr (cdr control)))))
    (list 'let (list (list '_dolist_iterator_ init))
	  (list 'while '_dolist_iterator_
	    (cons 'let
	      (cons (list (list var '(car _dolist_iterator_)))
		    (append body
			    (list (list 'setq '_dolist_iterator_
					(list 'cdr '_dolist_iterator_)))))))
	  val)))

(defvar xmms-buffer          nil "*The current xmms process buffer.")
(defvar xmms-playlist-buffer nil "*The current xmms playlist buffer.")
(defvar xmms-playlist-file "~/.xmms/xmms.m3u" "*The xmms persistent playlist.")

(defun inferior-xmms-mode ()
  "Major mode for interacting with an inferior Xmms process.

A Xmms process can be fired up with M-x run-xmms.

Customisation: Entry to this mode runs the hooks on comint-mode-hook and
inferior-xmms-mode-hook (in that order).

You can send text to the inferior Xmms process from other buffers containing
Xmms::Perl commands.  
    switch-to-xmms switches the current buffer to the Xmms process buffer.
    xmms-send-region sends the current region to the Xmms process.

If you accidentally suspend your process, use \\[comint-continue-subjob]
to continue it."
  (interactive)
  (comint-mode)
  ;; Customize in inferior-xmms-mode-hook
  (setq comint-prompt-regexp "^xmms>")
  ;;(xmms-mode-variables)
  (setq major-mode 'inferior-xmms-mode)
  (setq mode-name "Inferior Xmms")
  (setq mode-line-process '(":%s"))
  (use-local-map inferior-xmms-mode-map)
  (setq comint-input-filter (function xmms-input-filter))
  (setq comint-get-old-input (function xmms-get-old-input))
  (run-hooks 'inferior-xmms-mode-hook))

(defcustom inferior-xmms-filter-regexp "\\`\\s *\\S ?\\S ?\\s *\\'"
  "*Input matching this regexp are not saved on the history list.
Defaults to a regexp ignoring all inputs of 0, 1, or 2 letters."
  :type 'regexp
  :group 'xmms)

(defun xmms-input-filter (str)
  "Don't save anything matching inferior-xmms-filter-regexp"
  (not (string-match inferior-xmms-filter-regexp str)))

(defun xmms-get-old-input ()
  "Snarf the sexp ending at point"
  (save-excursion
    (let ((end (point)))
      (backward-sexp)
      (buffer-substring (point) end))))

(defun xmms-args-to-list (string)
  (let ((where (string-match "[ \t]" string)))
    (cond ((null where) (list string))
	  ((not (= where 0))
	   (cons (substring string 0 where)
		 (xmms-args-to-list (substring string (+ 1 where)
					       (length string)))))
	  (t (let ((pos (string-match "[^ \t]" string)))
	       (if (null pos)
		   nil
		 (xmms-args-to-list (substring string pos
					       (length string)))))))))

(defcustom xmms-program-name "perl -MXmms -e shell"
  "*Program invoked by the run-xmms command"
  :type 'string
  :group 'xmms)

;;;###autoload
(defun run-xmms (cmd)
  "Run an inferior Xmms process, input and output via buffer *xmms*.
If there is a process already running in `*xmms*', switch to that buffer.
With argument, allows you to edit the command line (default is value
of `xmms-program-name').  Runs the hooks `inferior-xmms-mode-hook'
\(after the `comint-mode-hook' is run).
\(Type \\[describe-mode] in the process buffer for a list of commands.)"

  (interactive (list (if current-prefix-arg
			 (read-string "Run Xmms: " xmms-program-name)
		       xmms-program-name)))
  (if (not (comint-check-proc "*xmms*"))
      (let ((cmdlist (xmms-args-to-list cmd)))
	(set-buffer (apply 'make-comint "xmms" (car cmdlist)
			   nil (cdr cmdlist)))
	(inferior-xmms-mode)
	(xmms-hide-all-windows)
	)
    )
  (setq xmms-program-name cmd)
  (setq xmms-buffer "*xmms*")
  (setq xmms-playlist-buffer "*xmms playlist*")
  ;;(pop-to-buffer "*xmms*")
  
  (find-file xmms-playlist-file)
  (rename-buffer "*xmms playlist*")
  (xmms-playlist-mode)
  )
;;;###autoload (add-hook 'same-window-buffer-names "*xmms*")

(defun switch-to-xmms (eob-p)
  "Switch to the xmms process buffer.
With argument, positions cursor at end of buffer."
  (interactive "P")
  (if (get-buffer xmms-buffer)
      (pop-to-buffer xmms-buffer)
    (error "No current process buffer. See variable xmms-buffer."))
  (cond (eob-p
	 (push-mark)
	 (goto-char (point-max)))))

(defun send-string (str)
;   (let ((buf (current-buffer)))
;     (pop-to-buffer xmms-buffer)
;     (insert-buffer str)
;     (comint-send-string (xmms-proc) str)
;     (switch-to-buffer buf)
;     )
  (comint-send-string (xmms-proc) str)
;;  (save-excursion
;;    (switch-to-buffer xmms-buffer)
;;    ;;(goto-char (point-max))
;;    (insert str)  
;;    (comint-send-string (xmms-proc) str)
;;    ;;(switch-to-buffer xmms-playlist-buffer)
;;    )
  )

(defun xmms-volume-slide-up ()
  "pump up the volume"
  (interactive)
  ;;(send-string "volume\n"))
  )

(defun xmms-volume-slide-down ()
  "tone it down"
  (interactive)
  ;;
  )

(defun xmms-next ()
  "play next track"
  (interactive)
  (send-string "next\n")
  )

(defun xmms-prev ()
  "play previous track"
  (interactive)
  (send-string "prev\n")
  )

(defun xmms-stop ()
  "stop playing"
  (interactive)
  (send-string "stop\n")
  )

(defun xmms-play ()
  "play"
  (interactive)
  (send-string "play\n")
  )

; (defun xmms-jtime ()
;   ""
;   (interactive)
;   (send-string "\n"))
;   )

; (defun xmms-mtime ()
;   ""
;   (interactive)
;   (send-string "\n"))
;   )

(defun xmms-pause ()
  "pause"
  (interactive)
  (send-string "pause\n")
)

(defun xmms-shuffle ()
  "shuffle play"
  (interactive)
  (send-string "shuffle\n")
)

(defun xmms-repeat ()
  "repeat track"
  (interactive)
  (send-string "repeat\n")
)

(defun xmms-play-track-1 ()
  "play track"
  (interactive)
  (send-string "\n")
)

(defun xmms-play-track-2 ()
  "play track"
  (interactive)
  (send-string "\n")
)

(defun xmms-play-track-3 ()
  "play track"
  (interactive)
  (send-string "\n")
)

(defun xmms-play-track-4 ()
  "play track"
  (interactive)
  (send-string "\n")
)

(defun xmms-play-track-5 ()
  "play track"
  (interactive)
  (send-string "\n")
)

(defun xmms-play-track-6 ()
  "play track"
  (interactive)
  (send-string "\n")
)

(defun xmms-play-track-7 ()
  "play track"
  (interactive)
  (send-string "\n")
)

(defun xmms-play-track-8 ()
  "play track"
  (interactive)
  (send-string "\n")
)

(defun xmms-play-track-9 ()
  "play track 9"
  (interactive)
  (send-string "\n")
)

(defun xmms-show-all-windows ()
  "show all windows"
  (interactive)
  (send-string "window all show\n")
)

(defun xmms-hide-all-windows ()
  "hide all windows"
  (interactive)
  (send-string "window all hide\n")
)

(defun xmms-main-window ()
  "show main window"
  (interactive)
  (send-string "window main show\n")
)

(defun xmms-playlist-window ()
  "show playlist window"
  (interactive)
  (send-string "window pl show\n")
)

(defun xmms-equalizer-window ()
  "show equalizer window"
  (interactive)
  (send-string "window eq show\n")
)

(defun xmms-quit ()
  "Kill the current xmms buffer."
  (interactive)
  (kill-buffer nil)
  (switch-to-buffer xmms-playlist-buffer)
  (kill-buffer nil)
  )

(defun xmms-proc ()
  "Returns the current xmms process. See variable xmms-buffer."
  (let ((proc (get-buffer-process (if (eq major-mode 'inferior-xmms-mode)
				      (current-buffer)
				    xmms-buffer))))
    (or proc
	(error "No current process. See variable xmms-buffer"))))

;;; Do the user's customisation...

(defcustom xmms-load-hook nil
  "This hook is run when xmms is loaded in.
This is a good place to put keybindings."
  :type 'hook
  :group 'xmms)
	
(run-hooks 'xmms-load-hook)

(provide 'xmms)

(defun xmms-current-descriptor ()
  "Return the descriptor of the current line, or signals an error."
  (nth (count-lines (point-min)
		    (save-excursion (beginning-of-line) (point)))
       xmms-parse-info) ;; lookup the entry in the array whose index is the current line #
  )

(defun xmms-tokenize (str)
  "chop off the 'str' string at the first '\n', return that part"
  
  (setq str (concat (if (string-match "[^\n]*\n" str)
			(substring str 0 (1- (match-end 0)))
		      str)))
  (cons str (match-end 0))
  )

(defvar xmms-playlist-mode-map nil "*Local keymap for xmms-playlist mode listings.")
(defvar xmms-playlist-parse-info nil) ;; this holds an array image of the playlist.
(defvar xmms-playlist-offset nil)

(put 'xmms-playlist-parse-info 'permanent-local t)

(if xmms-playlist-mode-map
    nil
  (setq xmms-playlist-mode-map (make-keymap))
  (suppress-keymap xmms-playlist-mode-map)
  (define-key xmms-playlist-mode-map "p" 'xmms-playlist-play)
  (define-key xmms-playlist-mode-map "\C-m" 'xmms-playlist-play)
  (define-key xmms-playlist-mode-map [mouse-2] 'xmms-playlist-extract)
  (define-key xmms-playlist-mode-map "q" 'xmms-playlist-quit)
  )

(defun xmms-playlist-play ()
  "play next track on playlist"
  (interactive)
  (message (xmms-playlist-current-descriptor))

;  (save-excursion
;    (switch-to-buffer xmms-buffer)
;    (send-string (concat "play '" (xmms-playlist-current-descriptor) "'\n")) ;; a quoted string in case there are embedded spaces
;    )

  (send-string (concat "play eval \"" (xmms-playlist-current-descriptor) "\"\n"))

  )

(defun xmms-playlist-current-descriptor ()
  "Return the descriptor of the current line, or signals an error."
  (nth (count-lines (point-min)
		    (save-excursion (beginning-of-line) (point)))
       xmms-playlist-parse-info) ;; lookup the entry in the array whose index is the current line #
  )

(defun xmms-playlist-tokenize (str)
  "chop off the 'str' string at the first '\n', return that part"
  
  (setq str (concat (if (string-match "[^\n]*\n" str)
			(substring str 0 (1- (match-end 0)))
		      str)))
  (cons str (match-end 0))
  )

(defun xmms-playlist-parse () ; analogous to tar-summarize-buffer
  "same strategy as in tar-mode, parse the data, show the parsed
in a narrowed region, hide the rest.
"
  (let* (
	 (result '())
	 (pos 1)
	 (max 0)
	 (token nil)
	 (str "")
	 )

    (message "Parsing xmms-playlist file...")
    (while (<= pos (point-max))
      (setq max (let ((nextpos (+ pos 128)))
		  (if (< nextpos (point-max))
		      nextpos
		    (point-max))))
      (setq token (xmms-playlist-tokenize (buffer-substring pos max)))
      (setq pos (+ pos (cdr token)))
      (let ((mp3file (car token)))
	
	(if (string-match ".*/\\([^/]+mp3\\)$" mp3file)
	    (progn
	      (setq str (concat str (substring mp3file (match-beginning 1) (match-end 1)) "\n"))
	      (setq result (cons mp3file result))
	      ))
	)
      )
    
    (setq xmms-playlist-parse-info (nreverse result))
        
    (save-excursion
    (goto-char (point-min))
    (let ()
 	(let (
	      (total-results str)
 	      )
 	  (if (multibyte-string-p total-results)
 	      (set-buffer-multibyte t))
 	  (insert total-results))
 	(make-local-variable 'xmms-playlist-offset)
 	(setq xmms-playlist-offset (point))
 	(narrow-to-region 1 xmms-playlist-offset) ; hide the end of the buffer...
 	(if enable-multibyte-characters
 	    (setq xmms-playlist-offset (position-bytes xmms-playlist-offset)))
 	(set-buffer-modified-p nil)))
    ))

;;;###autoload
(defun xmms-playlist-mode ()
  "Major mode for viewing a xmms-playlist file as a dired-like listing of its contents.
Unlike tar-mode, this one is interactive so that you can edit your playlist as a regular file 
as well (by toggling the narrowing off).
"
  (interactive)
  (kill-all-local-variables)
  (setq major-mode 'xmms-playlist-mode)
  (setq mode-name "Xmms Playlist")
  (use-local-map xmms-playlist-mode-map)
  (make-local-variable 'xmms-playlist-parse-info) ;; a separate playlist in each instance of this mode
  (widen)
  (xmms-playlist-parse)
  (run-hooks 'xmms-playlist-mode-hook)
  )

(defun xmms-playlist-quit ()
  "Kill the current xmms-playlist buffer."
  (interactive)
  (kill-buffer nil)
  (xmms-quit)
  )

(provide 'xmms-playlist-mode)

;;; xmms.el ends here
