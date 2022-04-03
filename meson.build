##
##  General
##  -------
##

project('libsupport', ['c'],
  version : '0.0.99',
  license : 'LGPL-2.1-or-later',
  default_options: [
    'warning_level=2',
    'c_std=gnu11',
    'werror=true',
  ],
  meson_version: '>=0.56.0',
)

add_project_arguments([
    '-D_GNU_SOURCE',
  ], language: 'c',
)

if get_option('debug')
  add_project_arguments(['-DDEBUG'], language: 'c')
endif


##
##  Compiler Configuration
##  ----------------------
##

cc = meson.get_compiler('c')

# strip relative path prefixes from the code if possible
if cc.has_argument('-fmacro-prefix-map=prefix=')
  add_project_arguments([
    '-fmacro-prefix-map=../=',
    ], language: 'c',
  )
endif


##
##  Subdirectories
##  --------------
##

# core
subdir('include')
subdir('src')


##
##  Run targets
##  -----------
##

# generate tags
ctags = find_program('ctags', required: false)
if ctags.found()
  run_target('ctags', command: [
    find_program('scripts/ctags.sh')
  ])
endif

# sparse
sparse = find_program('cgcc', required: false)
if sparse.found()
  run_target('sparse', command: [
    find_program('scripts/sparse.py'), 'compile_commands.json', sparse.full_path(),
    '-Wbitwise-pointer', '-Wconstant-suffix', '-Wshadow', '-Wundef', '-Wunion-cast',
    '-Wdeclaration-after-statement',
  ])
endif


##
##  Summaries
##  ---------
##

summary_info = {}
summary_info += {'Install prefix': get_option('prefix')}
summary_info += {'Binary directory': get_option('bindir')}
summary_info += {'Library directory': get_option('libdir')}
summary_info += {'Include directory': get_option('includedir')}
summary_info += {'Build directory': meson.current_build_dir()}
summary(summary_info, section: 'Directories')

summary_info = {}
summary_info += {'Host CPU': host_machine.cpu_family()}
summary_info += {'Host endianness': host_machine.endian()}
summary_info += {'C compiler': ' '.join(cc.cmd_array())}
summary_info += {'CFLAGS': ' '.join(get_option('c_args')
  + ['-O' + get_option('optimization')]
  + (get_option('debug') ? ['-g'] : []))}
summary_info += {'LDFLAGS': ' '.join(get_option('c_link_args'))}
summary(summary_info, section: 'Compilation')
