project('vcblockchain', 'c', 'cpp',
  default_options : ['c_std=gnu11', 'cpp_std=c++14', 'buildtype=release'],
  meson_version : '>=0.49.0'
)

message('Using build type: ' + get_option('buildtype'))

force_velo_toolchain = get_option('force_velo_toolchain')

if force_velo_toolchain
  cc = meson.get_compiler('c')
  cc_version = run_command(cc.cmd_array() + ['--version'], check : true).stdout()
  if not cc_version.contains('(velo)')
    error('force_velo_toolchain is set and you arn\'t using the velo toolchain.')
  endif
  cpp = meson.get_compiler('cpp')
  cpp_version = run_command(cpp.cmd_array() + ['--version'], check : true).stdout()
  if not cpp_version.contains('(velo)')
    error('force_velo_toolchain is set and you arn\'t using the velo toolchain.')
  endif
else
  warning('Not using the blessed velo gcc toolchain. Here be dragons.')
endif

add_project_arguments('-Wall', '-Werror', '-Wextra', language : 'c')
add_project_arguments('-Wall', '-Werror', '-Wextra', language : 'cpp')

src = run_command('find', './src', '-name', '*.c', check : true).stdout().strip().split('\n')
test_src = run_command('find', './test', '-name', '*.cpp', check : true).stdout().strip().split('\n')

# GTest is currently only used on native x86 builds. Creating a disabler will disable the test exe and test target.
if meson.is_cross_build()
  gtest = disabler()
else
  gtest = dependency('gtest', main : true, required : true, fallback : ['gtest','gtest_dep'])
endif

vcmodel = dependency('vcmodel',
  required : true,
  fallback : ['vcmodel', 'vcmodel_dep']
)

vpr = dependency('vpr',
  required : true,
  fallback : ['vpr', 'vpr_dep']
)

vcdb = dependency('vcdb',
  required : true,
  fallback : ['vcdb', 'vcdb_dep']
)

lmdb = dependency('lmdb',
  required : true,
  fallback : ['lmdb', 'lmdb_dep']
)

libevent = dependency('libevent',
  required : true,
  fallback : ['libevent', 'event_dep']
)

vccrypt = dependency('vccrypt',
  required : true,
  fallback : ['vccrypt', 'vccrypt_dep']
)

vccert = dependency('vccert',
  required : true,
  fallback : ['vccert', 'vccert_dep']
)

vpr_sub = subproject('vpr')
vpr_lib = vpr_sub.get_variable('vpr_lib')
vpr_include = vpr_sub.get_variable('vpr_include')

vccert_sub = subproject('vccert')
vccert_lib = vccert_sub.get_variable('vccert_lib')
vccert_include = vccert_sub.get_variable('vccert_include')

vccrypt_sub = subproject('vccrypt')
vccrypt_lib = vccrypt_sub.get_variable('vccrypt_lib')
vccrypt_include = vccrypt_sub.get_variable('vccrypt_include')

vcdb_sub = subproject('vcdb')
vcdb_lib = vcdb_sub.get_variable('vcdb_lib')
vcdb_include = vcdb_sub.get_variable('vcdb_include')

lmdb_sub = subproject('lmdb')
lmdb_include = lmdb_sub.get_variable('lmdb_inc')
lmdb_lib = lmdb_sub.get_variable('lmdb')

event_sub = subproject('libevent')
event_include = event_sub.get_variable('event_include')
event_lib = event_sub.get_variable('event_lib')

vcblockchain_include = include_directories('include')

objects = [
  vpr_lib.extract_all_objects(),
  vccert_lib.extract_all_objects(),
  vcdb_lib.extract_all_objects(),
  vccrypt_lib.extract_all_objects(),
  lmdb_lib.extract_all_objects(),
  event_lib.extract_all_objects()
]

vcblockchain_lib = static_library('vcblockchain', src,
  include_directories : vcblockchain_include,
  dependencies : [vcmodel, vpr, vcdb, lmdb, libevent, vccert, vccrypt],
  objects : objects
)

vcblockchain_test = executable('testvcblockchain', test_src,
  include_directories : vcblockchain_include,
  dependencies : [gtest, vpr, vccert, vcdb, vccrypt, lmdb, libevent],
  link_with : vcblockchain_lib
)

test('testvcblockchain', vcblockchain_test)

vcblockchain_dep = declare_dependency(
  link_with : vcblockchain_lib,
  include_directories : [
	vpr_include,
	vccert_include,
	vccrypt_include,
	vcdb_include,
	event_include,
    lmdb_include,
    vcblockchain_include
  ]
)
