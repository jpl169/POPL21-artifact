#include "float_math.h"
#include "log2.h"

double lut[128] =
{
    0.000000000000000000000000000000000000000000000000000000000000e+00,
    1.122725542325411947353064334720329497940838336944580078125000e-02,
    2.236781302845450986049868902227899525314569473266601562500000e-02,
    3.342300153745027951890378403732029255479574203491210937500000e-02,
    4.439411935845343631923398675098724197596311569213867187500000e-02,
    5.528243550118960153438862903385597746819257736206054687500000e-02,
    6.608919045777243705952486152455094270408153533935546875000000e-02,
    7.681559705083089439892063410297851078212261199951171875000000e-02,
    8.746284125033940148874478381912922486662864685058593750000000e-02,
    9.803208296052672021669849300451460294425487518310546875000000e-02,
    1.085244567781690483432299743071780540049076080322265625000000e-01,
    1.189410727235074294316774512481060810387134552001953125000000e-01,
    1.292830169449664667880028900981415063142776489257812500000000e-01,
    1.395513523987935433634532955693430267274379730224609375000000e-01,
    1.497471195046820580110136233997764065861701965332031250000000e-01,
    1.598713367783894112594822445316822268068790435791015625000000e-01,
    1.699250014423123733564580106758512556552886962890625000000000e-01,
    1.799090900149344640635007408491219393908977508544921875000000e-01,
    1.898245588800172301002788799451082013547420501708984375000000e-01,
    1.996723448363643960146163180979783646762371063232421875000000e-01,
    2.094533656289497836056057167297694832086563110351562500000000e-01,
    2.191685204621615645770305036421632394194602966308593750000000e-01,
    2.288186904958808831622718571452423930168151855468750000000000e-01,
    2.384047393250789126373234694256098009645938873291015625000000e-01,
    2.479275134435854899273010687466012313961982727050781250000000e-01,
    2.573878426926517470896271788660669699311256408691406250000000e-01,
    2.667865406949013751258803495147731155157089233398437500000000e-01,
    2.761244052742375387765605410095304250717163085937500000000000e-01,
    2.854022188622483691133879801782313734292984008789062500000000e-01,
    2.946207488916269823242544134700438007712364196777343750000000e-01,
    3.037807481771029327610733616893412545323371887207031250000000e-01,
    3.128829552843553352126093614060664549469947814941406250000000e-01,
    3.219280948873623482420214259036583825945854187011718750000000e-01,
    3.309168781146169524554068175348220393061637878417968750000000e-01,
    3.398500028846247467129160213517025113105773925781250000000000e-01,
    3.487281542310775583892734630353515967726707458496093750000000e-01,
    3.575520046180836741811503998178523033857345581054687500000000e-01,
    3.663222142458157915001493165618740022182464599609375000000000e-01,
    3.750394313469247453696198135730810463428497314453125000000000e-01,
    3.837042924740522442661472268810030072927474975585937500000000e-01,
    3.923174227787603052242104695324087515473365783691406250000000e-01,
    4.008794362821843093591667184227844700217247009277343750000000e-01,
    4.093909361377017774863418253517011180520057678222656250000000e-01,
    4.178525148858978632837590794224524870514869689941406250000000e-01,
    4.262647547020979588161537776613840833306312561035156250000000e-01,
    4.346282276367246510950792526273289695382118225097656250000000e-01,
    4.429434958487282747441327046544756740331649780273437500000000e-01,
    4.512111118323288150300243160017998889088630676269531250000000e-01,
    4.594316186372972565798988853202899917960166931152343750000000e-01,
    4.676055500829974231891128511051647365093231201171875000000000e-01,
    4.757334309663977522930622399144340306520462036132812500000000e-01,
    4.838157772642563969611728680320084095001220703125000000000000e-01,
    4.918530963296747215984794365795096382498741149902343750000000e-01,
    4.998458870832053757560231588286114856600761413574218750000000e-01,
    5.077946401986962454699892077769618481397628784179687500000000e-01,
    5.156998382840424222095521145092789083719253540039062500000000e-01,
    5.235619560570128339094253533403389155864715576171875000000000e-01,
    5.313814605163120763364759113756008446216583251953125000000000e-01,
    5.391588111080314327239193517016246914863586425781250000000000e-01,
    5.468944598876366303130680535105057060718536376953125000000000e-01,
    5.545888516776373844407999058603309094905853271484375000000000e-01,
    5.622424242210726230695172489504329860210418701171875000000000e-01,
    5.698556083309478381693224946502596139907836914062500000000000e-01,
    5.774288280357486868865635187830775976181030273437500000000000e-01,
    5.849625007211561866782290053379256278276443481445312500000000e-01,
    5.924570372680804108966867715935222804546356201171875000000000e-01,
    5.999128421871277039301162403717171400785446166992187500000000e-01,
    6.073303137496106618442581748240627348423004150390625000000000e-01,
    6.147098441152082370919629283889662474393844604492187500000000e-01,
    6.220518194563762204296608615550212562084197998046875000000000e-01,
    6.293566200796095744252056647383142262697219848632812500000000e-01,
    6.366246205436488780904369377822149544954299926757812500000000e-01,
    6.438561897747246964840428518073167651891708374023437500000000e-01,
    6.510516911789285821043904434191063046455383300781250000000000e-01,
    6.582114827517947519552876656234730035066604614257812500000000e-01,
    6.653359171851762621230363947688601911067962646484375000000000e-01,
    6.724253419714956159225494047859683632850646972656250000000000e-01,
    6.794800995054460779343230569793377071619033813476562500000000e-01,
    6.865005271832184119418229784059803932905197143554687500000000e-01,
    6.934869574993252072658833640161901712417602539062500000000000e-01,
    7.004397181410921824351589748403057456016540527343750000000000e-01,
    7.073591320808827465071999540668912231922149658203125000000000e-01,
    7.142455176661226534662318954360671341419219970703125000000000e-01,
    7.210991887071851458301807724637910723686218261718750000000000e-01,
    7.279204545631992040455315873259678483009338378906250000000000e-01,
    7.347096202258381891780913974798750132322311401367187500000000e-01,
    7.414669864011469435638446157099679112434387207031250000000000e-01,
    7.481928495894603070581752035650424659252166748046875000000000e-01,
    7.548875021634685600346870160137768834829330444335937500000000e-01,
    7.615512324444793090805205793003551661968231201171875000000000e-01,
    7.681843247769263305357867466227617114782333374023437500000000e-01,
    7.747870596011734445340835009119473397731781005859375000000000e-01,
    7.813597135246596048219203112239483743906021118164062500000000e-01,
    7.879025593914316116794793742883484810590744018554687500000000e-01,
    7.944158663501059702838347220676951110363006591796875000000000e-01,
    8.008998999203047475248240516521036624908447265625000000000000e-01,
    8.073549220576040630348302329366561025381088256835937500000000e-01,
    8.137811912170370698405008624831680208444595336914062500000000e-01,
    8.201789624151877289293111061851959675550460815429687500000000e-01,
    8.265484872909150126929489488247781991958618164062500000000000e-01,
    8.328900141647416210943788428266998380422592163085937500000000e-01,
    8.392037880969439589406988488917704671621322631835937500000000e-01,
    8.454900509443752376625980105018243193626403808593750000000000e-01,
    8.517490414160575618041093548526987433433532714843750000000000e-01,
    8.579809951275720880659036993165500462055206298828125000000000e-01,
    8.641861446542802305259556305827572941780090332031250000000000e-01,
    8.703647195834045557916169855161570012569427490234375000000000e-01,
    8.765169465649996771716701005061622709035873413085937500000000e-01,
    8.826430493618412365108838457672391086816787719726562500000000e-01,
    8.887432488982590639281511357694398611783981323242187500000000e-01,
    8.948177633079434922791506323846988379955291748046875000000000e-01,
    9.008668079807485851162596190988551825284957885742187500000000e-01,
    9.068905956085184794090991999837569892406463623046875000000000e-01,
    9.128893362299616009991609644202981144189834594726562500000000e-01,
    9.188632372745945131597977706405799835920333862304687500000000e-01,
    9.248125036057809333911450266896281391382217407226562500000000e-01,
    9.307373375628862355313231091713532805442810058593750000000000e-01,
    9.366379390025705298228331230347976088523864746093750000000000e-01,
    9.425145053392398608593794051557779312133789062500000000000000e-01,
    9.483672315846776168513088123290799558162689208984375000000000e-01,
    9.541963103868752460456903463636990636587142944335937500000000e-01,
    9.600019320680809320478488189110066741704940795898437500000000e-01,
    9.657842846620869892149130464531481266021728515625000000000000e-01,
    9.715435539507719653329331777058541774749755859375000000000000e-01,
    9.772799234999164363912882436125073581933975219726562500000000e-01,
    9.829935746943101460004754699184559285640716552734375000000000e-01,
    9.886846867721658105310211794858332723379135131835937500000000e-01,
    9.943534368588579086534195994317997246980667114257812500000000e-01
};

double oneByF[128] = {
    1.000000000000000000000000000000000000000000000000000000000000,
    0.992248062015503862198784190695732831954956054687500000000000,
    0.984615384615384670041748904623091220855712890625000000000000,
    0.977099236641221335908369383105309680104255676269531250000000,
    0.969696969696969723884194536367431282997131347656250000000000,
    0.962406015037593931538140168413519859313964843750000000000000,
    0.955223880597014907145592133019817993044853210449218750000000,
    0.948148148148148184333194876671768724918365478515625000000000,
    0.941176470588235281056199710292275995016098022460937500000000,
    0.934306569343065662636149681929964572191238403320312500000000,
    0.927536231884057982277624887501588091254234313964843750000000,
    0.920863309352518033534806818352080881595611572265625000000000,
    0.914285714285714257165693652495974674820899963378906250000000,
    0.907801418439716290009755539358593523502349853515625000000000,
    0.901408450704225372440703267784556373953819274902343750000000,
    0.895104895104895104118725157604785636067390441894531250000000,
    0.888888888888888839545643349993042647838592529296875000000000,
    0.882758620689655160163056279998272657394409179687500000000000,
    0.876712328767123239003922208212316036224365234375000000000000,
    0.870748299319727858680550980352563783526420593261718750000000,
    0.864864864864864912874509172979742288589477539062500000000000,
    0.859060402684563739761358647228917106986045837402343750000000,
    0.853333333333333388104335881507722660899162292480468750000000,
    0.847682119205298012509786076407181099057197570800781250000000,
    0.842105263157894690095872647361829876899719238281250000000000,
    0.836601307189542509057389452209463343024253845214843750000000,
    0.831168831168831223621396020462270826101303100585937500000000,
    0.825806451612903225090178693790221586823463439941406250000000,
    0.820512820512820484353255778842139989137649536132812500000000,
    0.815286624203821697065563967043999582529067993164062500000000,
    0.810126582278481000010117440979229286313056945800781250000000,
    0.805031446540880546436369513685349375009536743164062500000000,
    0.800000000000000044408920985006261616945266723632812500000000,
    0.795031055900621064225219924992416054010391235351562500000000,
    0.790123456790123412929460755549371242523193359375000000000000,
    0.785276073619631920230688137962715700268745422363281250000000,
    0.780487804878048807566415234759915620088577270507812500000000,
    0.775757575757575756902895136590814217925071716308593750000000,
    0.771084337349397630489988841873127967119216918945312500000000,
    0.766467065868263519590186660934705287218093872070312500000000,
    0.761904761904761862467694299994036555290222167968750000000000,
    0.757396449704141994097028600663179531693458557128906250000000,
    0.752941176470588224844959768233820796012878417968750000000000,
    0.748538011695906391196331242099404335021972656250000000000000,
    0.744186046511627896649088143021799623966217041015625000000000,
    0.739884393063583778449299188650911673903465270996093750000000,
    0.735632183908045966802546899998560547828674316406250000000000,
    0.731428571428571427937015414499910548329353332519531250000000,
    0.727272727272727292913145902275573462247848510742187500000000,
    0.723163841807909602010795424575917422771453857421875000000000,
    0.719101123595505598018462478648871183395385742187500000000000,
    0.715083798882681587194554140296531841158866882324218750000000,
    0.711111111111111138249896157503826543688774108886718750000000,
    0.707182320441988920833864540327340364456176757812500000000000,
    0.703296703296703351604435283661587163805961608886718750000000,
    0.699453551912568305404249713319586589932441711425781250000000,
    0.695652173913043458952643049997277557849884033203125000000000,
    0.691891891891891930299607338383793830871582031250000000000000,
    0.688172043010752743086300142749678343534469604492187500000000,
    0.684491978609625628671153663162840530276298522949218750000000,
    0.680851063829787217507316654518945142626762390136718750000000,
    0.677248677248677211082394933328032493591308593750000000000000,
    0.673684210526315774281158610392594709992408752441406250000000,
    0.670157068062827265819692001969087868928909301757812500000000,
    0.666666666666666629659232512494781985878944396972656250000000,
    0.663212435233160646497196921700378879904747009277343750000000,
    0.659793814432989678131491473322967067360877990722656250000000,
    0.656410256410256409687065115576842799782752990722656250000000,
    0.653061224489795866254837619635509327054023742675781250000000,
    0.649746192893400964507577555195894092321395874023437500000000,
    0.646464646464646519596897178416838869452476501464843750000000,
    0.643216080402010059735573577199829742312431335449218750000000,
    0.640000000000000013322676295501878485083580017089843750000000,
    0.636815920398009938097061422013211995363235473632812500000000,
    0.633663366336633671060951655817916616797447204589843750000000,
    0.630541871921182273119654837501002475619316101074218750000000,
    0.627450980392156854037466473528183996677398681640625000000000,
    0.624390243902439023848671695304801687598228454589843750000000,
    0.621359223300970819892086183244828134775161743164062500000000,
    0.618357487922705284510982437495840713381767272949218750000000,
    0.615384615384615418776093065389432013034820556640625000000000,
    0.612440191387559784708116694673663005232810974121093750000000,
    0.609523809523809578791997410007752478122711181640625000000000,
    0.606635071090047439668069273466244339942932128906250000000000,
    0.603773584905660354316125904006185010075569152832031250000000,
    0.600938967136150248293802178523037582635879516601562500000000,
    0.598130841121495282486364430951653048396110534667968750000000,
    0.595348837209302317319270514417439699172973632812500000000000,
    0.592592592592592559697095566662028431892395019531250000000000,
    0.589861751152073732207270495564443990588188171386718750000000,
    0.587155963302752326171685126610100269317626953125000000000000,
    0.584474885844748826002614805474877357482910156250000000000000,
    0.581818181818181789921595736814197152853012084960937500000000,
    0.579185520361991001969670378457522019743919372558593750000000,
    0.576576576576576571575571961147943511605262756347656250000000,
    0.573991031390134520684398466983111575245857238769531250000000,
    0.571428571428571396850770724995527416467666625976562500000000,
    0.568888888888888888395456433499930426478385925292968750000000,
    0.566371681415929195679836993804201483726501464843750000000000,
    0.563876651982378906957649178366409614682197570800781250000000,
    0.561403508771929793397248431574553251266479492187500000000000,
    0.558951965065502154317300664843060076236724853515625000000000,
    0.556521739130434789366574932500952854752540588378906250000000,
    0.554112554112554112073496526136295869946479797363281250000000,
    0.551724137931034475101910174998920410871505737304687500000000,
    0.549356223175965663330089228111319243907928466796875000000000,
    0.547008547008547063583705494238529354333877563476562500000000,
    0.544680851063829796210313816118286922574043273925781250000000,
    0.542372881355932201508096568431938067078590393066406250000000,
    0.540084388185653962999310806480934843420982360839843750000000,
    0.537815126050420144743213768379064276814460754394531250000000,
    0.535564853556485309660217808414017781615257263183593750000000,
    0.533333333333333325931846502498956397175788879394531250000000,
    0.531120331950207469340341503993840888142585754394531250000000,
    0.528925619834710758482287928927689790725708007812500000000000,
    0.526748971193415682634508812043350189924240112304687500000000,
    0.524590163934426256808762900618603453040122985839843750000000,
    0.522448979591836781821712065720930695533752441406250000000000,
    0.520325203252032575385044310678495094180107116699218750000000,
    0.518218623481781381912014694535173475742340087890625000000000,
    0.516129032258064501803573875804431736469268798828125000000000,
    0.514056224899598346311790919571649283170700073242187500000000,
    0.512000000000000010658141036401502788066864013671875000000000,
    0.509960159362549791950414146413095295429229736328125000000000,
    0.507936507936507908311796199996024370193481445312500000000000,
    0.505928853754940677234230861358810216188430786132812500000000,
    0.503937007874015741037965199211612343788146972656250000000000,
    0.501960784313725483229973178822547197341918945312500000000000
};

float mylog2(float x) {
    floatX fix, fit;
    fix.f = x;
    int m = 0;
    
    if (fix.x < 0x800000 || fix.x >= 0x7F800000) {
        if ((fix.x & 0x7FFFFFFF) == 0) { // log(+/-0) = -infty
            fix.x = 0xFF800000;
            return fix.f;
        }
        
        if (fix.x > 0x7FFFFFFF) { // Log(-val) = NaN
            return (x-x) / 0;
            
        }
        
        if (fix.x >= 0x7F800000) {
            return x + x;
        }
        
        fix.f *= pow(2, 23);
        m -= 23;
    }
    
    m += fix.x >> 23;
    m -= 127;
    fix.x &= 0x007FFFFF;
    fix.x |= 0x3F800000;
    
    fit.x = fix.x & 0x007F0000;
    int FIndex = fit.x >> 16;
    fit.x |= 0x3F800000;
    
    double f = fix.f - fit.f;
    double modifier = m + lut[FIndex];
    f *= oneByF[FIndex];
    
    double y = C_1_5;
    y *= f;
    y += C_1_4;
    y *= f;
    y += C_1_3;
    y *= f;
    y += C_1_2;
    y *= f;
    y += C_1_1;
    y *= f;
    
    return y + modifier;
}
