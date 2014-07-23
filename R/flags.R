RcppMLPACK.system.file <- function(...){
    tools::file_path_as_absolute( base::system.file( ..., package = "RcppMLPACK" ) )
}

staticLinking <- function() {
    ! grepl( "^linux", R.version$os )
}

RcppMLPACKLdPath <- function() {
    if (nzchar(.Platform$r_arch)) {	## eg amd64, ia64, mips
        path <- RcppMLPACK.system.file("lib",.Platform$r_arch)
    } else {
        path <- RcppMLPACK.system.file("lib")
    }
    path
}

RcppMLPACKLdFlags <- function(static=staticLinking()) {
    RcppMLPACKdir <- RcppMLPACKLdPath()
    if (static) {                               # static is default on Windows and OS X
        flags <- paste(RcppMLPACKdir, "/libRcppMLPACK.a", sep="")
    } else {					# else for dynamic linking
        flags <- paste("-L", RcppMLPACKdir, " -lRcppMLPACK", sep="") # baseline setting
        if ((.Platform$OS.type == "unix") &&    # on Linux, we can use rpath to encode path
            (length(grep("^linux",R.version$os)))) {
            flags <- paste(flags, " -Wl,-rpath,", RcppMLPACKdir, sep="")
        }
    }
    invisible(flags)
}

CxxFlags <- function() {
    path <- RcppMLPACK.system.file("include")
    paste("-I", path, sep="")
}

LdFlags <- function(static=staticLinking()) {
    cat(RcppMLPACKLdFlags(static=static))
}
