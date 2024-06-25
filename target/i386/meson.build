i386_ss = ss.source_set()
i386_ss.add(files(
  'cpu.c',
  'gdbstub.c',
  'helper.c',
  'xsave_helper.c',
  'cpu-dump.c',
))
i386_ss.add(when: 'CONFIG_SEV', if_true: files('host-cpu.c'))

# x86 cpu type
i386_ss.add(when: 'CONFIG_KVM', if_true: files('host-cpu.c'))
i386_ss.add(when: 'CONFIG_HVF', if_true: files('host-cpu.c'))

i386_system_ss = ss.source_set()
i386_system_ss.add(files(
  'arch_dump.c',
  'arch_memory_mapping.c',
  'machine.c',
  'monitor.c',
  'cpu-sysemu.c',
))
i386_system_ss.add(when: 'CONFIG_SEV', if_true: files('sev.c'), if_false: files('sev-sysemu-stub.c'))

i386_user_ss = ss.source_set()

subdir('kvm')
subdir('whpx')
subdir('nvmm')
subdir('hvf')
subdir('tcg')

if llvm_to_tcg_enabled
    h2tcg = subproject('helper2tcg', required: true)
    h2tcg_get_llvm_ir = h2tcg.get_variable('get_llvm_ir')
    h2tcg_pipeline = h2tcg.get_variable('pipeline')
endif

i386_user_ss.add(files('tcg_global_mappings.c'))
if llvm_to_tcg_enabled
    h2tcg_input_files = [
        meson.current_source_dir() / 'tcg/int_helper.c',
        meson.current_source_dir() / 'tcg/excp_helper.c',
        meson.current_source_dir() / 'tcg_global_mappings.c',
    ]

    ll = h2tcg_get_llvm_ir.process(h2tcg_input_files, extra_args: 'target/i386')

    helper2tcg = custom_target('helper2tcg',
        output: ['helper2tcg-emitted.c',
                 'helper2tcg-emitted.h',
                 'helper2tcg-enabled',
                 'helper2tcg-log'],
        input: [ll],
        depends: [h2tcg_pipeline, helper_funcs_generated, helper_protos_generated],
        command: [h2tcg_pipeline,
                  '--output-source=@OUTPUT0@',
                  '--output-header=@OUTPUT1@',
                  '--output-enabled=@OUTPUT2@',
                  '--output-log=@OUTPUT3@',
                  '@INPUT@']
      )

    i386_user_ss.add(helper2tcg)
endif

target_arch += {'i386': i386_ss}
target_system_arch += {'i386': i386_system_ss}
target_user_arch += {'i386': i386_user_ss}
